# Minishell2 (EPITECH) - Project README

This repository contains a custom shell named `mysh`, built as the continuation of a first project (`minishell1`).

- `minishell1` scope: basic builtins + execution of external binaries.
- `minishell2` scope: extends the shell with lexical analysis, parsing to an AST, pipelines, command sequences, and redirections.

The implementation is in C and split into small modules to keep parsing, execution, builtins, and environment management clearly separated.

## 1) Build and Run

### Build

```bash
make
```

This produces the executable:

- `mysh`

### Run

```bash
./mysh
```

If stdin is a TTY, the prompt displayed is:

```text
$> 
```

### Clean

```bash
make clean
make fclean
```

## 2) Main Features Implemented

- External command execution (`execve`) with `PATH` search.
- Builtins:
	- `cd`
	- `env`
	- `setenv`
	- `unsetenv`
- Exit code tracking in `shell->last_status`.
- `$?` substitution in command arguments before external execution.
- Tokenization (lexer) into operators/words.
- Parsing into an AST with:
	- command nodes
	- sequence nodes (`;`)
	- pipeline nodes (`|`)
- Redirections:
	- input `<`
	- output `>`
	- append `>>`
	- heredoc `<<`

## 3) Runtime Flow (High-Level)

1. `main()` creates and initializes a `shell_t`.
2. `shell_run()` performs the read-execute loop with `getline`.
3. Input line is tokenized by the lexer.
4. Tokens are parsed into an AST (`AST_COMMAND`, `AST_SEQUENCE`, `AST_PIPE`).
5. `exec_ast()` walks the AST and executes:
	 - sequence left then right,
	 - pipeline through `pipe()` + `fork()`,
	 - single commands via builtin dispatch or external exec.
6. Status code is stored in `shell->last_status` and reused (`$?`).

## 4) Core Data Structures

### Shell State (`shell_t`)

Defined in `include/shell.h`:

- `char **env`: current mutable environment.
- `int last_status`: last command exit status.
- `int interactive`: whether stdin is a terminal (`isatty`).
- `char *line` / `size_t line_cap`: `getline` buffer and capacity.

### Command (legacy/simple split structure)

Defined in `include/loop.h`:

- `command_t` stores `argv` + `argc`.

It is used by builtin/external dispatch helpers and by the command execution bridge.

### Tokens

Defined in `include/token.h`:

- `TOK_ARGS`
- `TOK_SEMICOLON`
- `TOK_PIPE`
- `TOK_LESS_THAN`
- `TOK_GREATER_THAN`
- `TOK_DOUBLE_LESS_THAN`
- `TOK_DOUBLE_GREATER_THAN`
- `TOK_EOF`

### AST

Defined in `include/parser.h`:

- `AST_COMMAND`
- `AST_SEQUENCE`
- `AST_PIPE`

For command nodes, `ast_command_t` stores:

- `argv`
- linked list of `redir_t`

## 5) Code Organization by Folder

## `src/main.c`

- Program entry point.
- Validates startup arguments, creates shell, initializes env, starts loop.

## `src/shell/`

- `shell_create.c`: allocates shell object and sets defaults.
- `shell_init.c`: duplicates inherited env and applies shell-specific initialization.
- `shell_destroy.c`: frees line buffer, env array, and shell object.

## `src/loop/`

Contains command dispatch and low-level process execution helpers.

- `loop_terminal.c`
	- prompt display,
	- `getline` read loop,
	- empty-line/exit handling,
	- lexer + parser + AST execution orchestration.
- `my_exec.c`
	- builtin detection and execution,
	- fallback to external execution,
	- status/error mapping (`127` -> command not found, `126` -> permission denied).
- `command.c` / `command_destroy.c`
	- simple line split with `str_to_word_array`,
	- lifecycle of `command_t`.
- `get_command_code.c`
	- replaces literal `$?` args with previous status.
- `fork_process.c`
	- executes command directly if path contains `/`, otherwise searches in `PATH`.
	- waits child and returns shell-style status (including signal handling).

## `src/lexer/`

- `lexer_create.c` / `lexer_destroy.c`: lexer lifecycle.
- `lexer_tokenize.c`: scans input and emits tokens for words/operators.
- `token/`
	- `token_create.c`: token allocation + value duplication.
	- `token_destroy.c`: token memory cleanup.

## `src/parser/`

Builds and executes the AST.

- `parser.c`
	- parses command bodies, redirections, pipelines, and sequences.
- `ast.c`
	- AST node constructors,
	- recursive AST destruction.
- `parser_utils.c`
	- helper functions for string duplication and redirection metadata.
- `executor.c`
	- recursive AST execution,
	- sequence order,
	- pipeline setup and child process coordination.
- `redirection.c`
	- opens files/pipe endpoints for redirections,
	- applies `dup2`,
	- heredoc read loop until delimiter.

## `src/builtin/`

- `builtin_env.c`: `env` builtin with argument validation.
- `builtin_setenv.c`: `setenv` validation and env update.
- `change_directory.c`: `cd` implementation (`~`, `-`, direct path) and `PWD`/`OLDPWD` updates.

## `src/env/`

Environment array management (`char **env`):

- count/search/duplication/free:
	- `count_env.c`
	- `find_env_index.c`
	- `dup_env.c`
	- `free_env.c`
- mutation helpers:
	- `update_env.c` (insert or replace key=value)
	- `remove_env_key.c`
	- `unsetenv.c` (builtin-side unset)
- initialization and output:
	- `init_shell_env.c` (startup normalization, including `NLSPATH` handling)
	- `print_env.c`

## `lib/`

Custom utility library used across the project:

- string functions (`my_strlen`, `my_strcmp`, `my_strdup`, ...)
- output helpers (`my_putstr`, `put_on_fd`, ...)
- converters (`my_int_to_str`)
- tokenization helper (`str_to_word_array`)

## `include/`

Public headers for each subsystem (`shell`, `loop`, `lexer`, `parser`, `env`, `builtin`, `token`, utilities).

## 6) Builtin Behavior Summary

- `env`
	- prints environment if no extra args.
	- returns error code `1` for too many arguments.

- `setenv`
	- with no args: prints environment.
	- with one or two args: sets/updates variable.
	- validates variable name starts with a letter and remains alphanumeric.

- `unsetenv`
	- requires at least one key.
	- removes each requested key from the env array.

- `cd`
	- no arg or `~`: goes to `HOME`.
	- `-`: goes to `OLDPWD`.
	- path: attempts `chdir(path)`.
	- updates `OLDPWD` then `PWD` on success.

## 7) Error and Exit Code Handling

- Internal fatal errors generally return `ERROR` (`84`) at function level.
- Command execution status follows shell conventions where possible:
	- normal child exit code,
	- `128 + signal` on signal termination,
	- `127` command not found,
	- `126` permission denied.

## 8) Known Scope / Limitations

Current implementation intentionally focuses on the minishell2 educational scope.
Notable limitations compared to a full POSIX shell:

- no quote/escape-aware lexer,
- no variable expansion beyond literal `$?`,
- no logical operators (`&&`, `||`),
- no job control,
- no advanced globbing,
- no subshells.

## 9) Project Context (for recruiters/correctors)

This was completed as a one-week EPITECH project and follows a progressive design:

1. `minishell1`: base shell features (core builtins + external binaries).
2. `minishell2`: parser/executor architecture with AST, pipelines, and redirections.

The codebase is organized to show clear separation of concerns and maintainability despite tight delivery time.
