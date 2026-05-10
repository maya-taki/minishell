# Minishell Parser — Development Guide (42 School)

## Project Overview

This guide covers the complete development of the **Parser** for the Minishell project at École 42,
based on the code already written (lexer, tokens, structs, error handling). The parser receives the
`t_token` list produced by the lexer and builds the `t_cmd` list that will be executed.

```
input (char*)
    │
    ▼
 [LEXER]   → validates quotes/invalid operators → produces t_token*
    │
    ▼
[SYNTAX]   → validate_syntax(t_token*) → checks structural errors
    │
    ▼
[PARSER]   → builds t_cmd* with args and redirections
    │
    ▼
[EXECUTOR] → runs the pipeline
```

---

## Code Analysis — Bugs & Inconsistencies

### Bug 1: `t_redir.type` declared as a pointer

**File:** `structs.h`

```c
/* CURRENT — WRONG */
typedef struct s_redir
{
    t_token_type    *type;   /* pointer to enum causes UB on comparison */
    char            *file;
    struct s_redir  *next;
}   t_redir;

/* CORRECT */
typedef struct s_redir
{
    t_token_type    type;    /* enum by value, not pointer */
    char            *file;
    struct s_redir  *next;
}   t_redir;
```

The `type` field is declared as `t_token_type *` (pointer to enum) instead of `t_token_type`
(value). Any comparison like `redir->type == TOKEN_REDIR_IN` would be comparing memory addresses,
not enum values — silent undefined behavior.

---

### Bug 2: `count_words` passes `token` instead of `tmp` to `is_redir`

**File:** `parser_utils.c`

```c
/* CURRENT — WRONG */
int count_words(t_token *token)
{
    int     counter;
    t_token *tmp;

    counter = 0;
    tmp = token;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (tmp->type == TOKEN_WORD)
            counter++;
        if (is_redir(token))   /* BUG: always tests the list head, not current node */
        {
            tmp = tmp->next;
            continue ;
        }
        tmp = tmp->next;
    }
    return (counter);
}

/* CORRECT */
int count_words(t_token *token)
{
    int     counter;
    t_token *tmp;

    counter = 0;
    tmp = token;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (is_redir(tmp))        /* uses 'tmp' — the current node */
        {
            tmp = tmp->next;      /* skip the redirect operator */
            if (tmp)
                tmp = tmp->next;  /* skip the filename that follows */
            continue ;
        }
        if (tmp->type == TOKEN_WORD)
            counter++;
        tmp = tmp->next;
    }
    return (counter);
}
```

The current version always evaluates `is_redir` against the **head** of the list (`token`), never
the current node. Additionally, when a redirect is found, two tokens must be skipped: the operator
(`<`, `>`, etc.) and the filename that follows it — otherwise the filename gets counted as a
command argument.

---

### Bug 3: `validate_syntax` returns `ERR_SYNTAX` (value 1) and `1` for success — ambiguous

**File:** `syntax.c`

```c
/* ERR_SYNTAX == 1, but success also returns 1 — impossible to distinguish */
int validate_syntax(t_token *tokens)
{
    ...
    return (ERR_SYNTAX); /* == 1 */
    ...
    return (1);          /* success is also 1 */
}
```

`ERR_NONE` equals `0` and `ERR_SYNTAX` equals `1` in the `e_error_type` enum. The function returns
`1` for both success and error — completely indistinguishable by the caller. Fix: return `0` for
success and the error code for failure.

```c
/* CORRECT */
int validate_syntax(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    if (!tmp)
        return (0);
    if (tmp->type == TOKEN_PIPE)
        return (ERR_SYNTAX);
    while (tmp)
    {
        if (!tmp->next && tmp->type != TOKEN_WORD)
            return (ERR_SYNTAX);
        if (tmp->type == TOKEN_PIPE && tmp->next
            && tmp->next->type == TOKEN_PIPE)
            return (ERR_SYNTAX);
        tmp = tmp->next;
    }
    return (0); /* success == 0 */
}
```

**Side note:** the original check `tmp->next->type` has a potential null dereference if `tmp->next`
is `NULL`. The corrected version above includes that guard.

---

### Bug 4: `validate_syntax` does not catch a redirect without a filename

The current `validate_syntax` does not detect a redirect token at the end of the list (e.g.,
`echo hello >`). Add this check inside the loop:

```c
if (is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD))
    return (ERR_SYNTAX);
```

---

### Bug 5: Syntax error in the lexer uses `ft_printf` instead of `handle_error`

**File:** `lexer.c`

```c
/* CURRENT */
ft_printf(RED"syntax error\n"RST); /* prints to stdout, bypasses error system */

/* CORRECT */
handle_error(ERR_SYNTAX, NULL, "newline"); /* prints to stderr, consistent */
```

The centralised error system (`handle_error`) already exists in `error_utils.c` and writes to
`STDERR_FILENO`. Using `ft_printf` here writes to stdout, which breaks both consistency and bash
behaviour (bash always prints syntax errors to stderr).

---

## Suggested `t_redir` Structure

The current struct only stores `type` and `file`. For heredoc support, the delimiter and expansion
flag are also needed (quoted delimiters disable `$VAR` expansion inside the heredoc body):

```c
typedef struct s_redir
{
    t_token_type    type;
    char            *file;    /* filename for <, >, >>; delimiter for << */
    int             expand;   /* 1 = expand $VAR; 0 = literal (heredoc with quotes) */
    struct s_redir  *next;
}   t_redir;
```

---

## Full Parser Implementation

### Function Map

| Function | File | Responsibility |
|---|---|---|
| `parser` | `parser.c` | Entry point: receives `t_mini*`, orchestrates everything |
| `parse_cmd` | `parser.c` | Builds one `t_cmd` (args + redirs) for a pipeline segment |
| `fill_args` | `parser.c` | Allocates and fills `cmd->cmd_args` |
| `fill_redirs` | `parser.c` | Walks the segment and calls `add_redir` for each redirect |
| `add_redir` | `redirects.c` | Allocates and appends one `t_redir` to the cmd's redir list |
| `new_cmd` | `parser_utils.c` | Allocates and zero-initialises a `t_cmd` |
| `count_words` | `parser_utils.c` | Counts word tokens in a segment (corrected) |
| `count_cmds` | `parser_utils.c` | Counts pipeline segments separated by pipes |
| `validate_syntax` | `syntax.c` | Validates the token list structure (corrected) |

---

### `parser.c` — Full Implementation

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+      */
/*   By: mtakiyos <mtakiyos@student.42.fr>        +#+  +:+       +#+         */
/*                                              +#+#+#+#+#+   +#+             */
/*   Created: 2026/04/23 19:00:55 by mtakiyos         #+#    #+#             */
/*   Updated: 2026/05/09 00:00:00 by mtakiyos        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int  fill_args(t_token *seg_start, t_cmd *cmd)
{
    t_token *tmp;
    int     j;

    cmd->cmd_args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
    if (!cmd->cmd_args)
        return (1);
    tmp = seg_start;
    j = 0;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (is_redir(tmp))
        {
            tmp = tmp->next;
            if (tmp)
                tmp = tmp->next;
            continue ;
        }
        if (tmp->type == TOKEN_WORD)
        {
            cmd->cmd_args[j] = ft_strdup(tmp->value);
            if (!cmd->cmd_args[j])
                return (1);
            j++;
        }
        tmp = tmp->next;
    }
    cmd->cmd_args[j] = NULL;
    return (0);
}

static int  fill_redirs(t_token *seg_start, t_cmd *cmd)
{
    t_token *tmp;

    tmp = seg_start;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (is_redir(tmp))
        {
            if (!tmp->next || tmp->next->type != TOKEN_WORD)
                return (ERR_SYNTAX);
            if (add_redir(cmd, tmp->type, tmp->next->value))
                return (ERR_MALLOC);
            tmp = tmp->next->next;
            continue ;
        }
        tmp = tmp->next;
    }
    return (0);
}

static t_cmd    *parse_cmd(t_token *seg_start)
{
    t_cmd   *cmd;
    int     err;

    cmd = new_cmd();
    if (!cmd)
        return (NULL);
    err = fill_args(seg_start, cmd);
    if (err)
    {
        free_cmd(cmd);
        return (NULL);
    }
    err = fill_redirs(seg_start, cmd);
    if (err)
    {
        free_cmd(cmd);
        return (NULL);
    }
    return (cmd);
}

t_cmd   *parser(t_mini *mini)
{
    t_token *tmp;
    t_cmd   *head;
    t_cmd   *cmd;
    t_cmd   *last;

    if (!mini || !mini->tokens)
        return (NULL);
    if (validate_syntax(mini->tokens))
    {
        handle_error(ERR_SYNTAX, NULL, "unexpected token");
        return (NULL);
    }
    head = NULL;
    last = NULL;
    tmp = mini->tokens;
    while (tmp)
    {
        cmd = parse_cmd(tmp);
        if (!cmd)
        {
            free_cmds(head);
            return (NULL);
        }
        if (!head)
            head = cmd;
        else
            last->next = cmd;
        last = cmd;
        while (tmp && tmp->type != TOKEN_PIPE)
            tmp = tmp->next;
        if (tmp && tmp->type == TOKEN_PIPE)
            tmp = tmp->next;
    }
    return (head);
}
```

---

### `redirects.c` — `is_redir` and `add_redir`

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                       :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+      */
/*   By: mtakiyos <mtakiyos@student.42.fr>        +#+  +:+       +#+         */
/*                                              +#+#+#+#+#+   +#+             */
/*   Created: 2026/05/06 14:32:53 by mtakiyos         #+#    #+#             */
/*   Updated: 2026/05/09 00:00:00 by mtakiyos        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int is_redir(t_token *token)
{
    return (token->type == TOKEN_HEREDOC
        || token->type == TOKEN_REDIR_OUT
        || token->type == TOKEN_REDIR_APPEND
        || token->type == TOKEN_REDIR_IN);
}

int add_redir(t_cmd *cmd, t_token_type type, char *file)
{
    t_redir *redir;
    t_redir *last;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (1);
    redir->type = type;
    redir->file = ft_strdup(file);
    if (!redir->file)
    {
        free(redir);
        return (1);
    }
    redir->next = NULL;
    if (!cmd->redirs)
    {
        cmd->redirs = redir;
        return (0);
    }
    last = cmd->redirs;
    while (last->next)
        last = last->next;
    last->next = redir;
    return (0);
}
```

---

### `parser_utils.c` — `new_cmd`, `count_words`, `count_cmds`, `open_file`

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                    :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+      */
/*   By: mtakiyos <mtakiyos@student.42.fr>        +#+  +:+       +#+         */
/*                                              +#+#+#+#+#+   +#+             */
/*   Created: 2026/05/06 14:38:01 by mtakiyos         #+#    #+#             */
/*   Updated: 2026/05/09 00:00:00 by mtakiyos        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd   *new_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd_args = NULL;
    cmd->cmd_path = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

int count_cmds(t_token *token_list)
{
    int     len;
    t_token *tmp;

    len = 1;
    tmp = token_list;
    while (tmp)
    {
        if (tmp->type == TOKEN_PIPE)
            len++;
        tmp = tmp->next;
    }
    return (len);
}

int count_words(t_token *token)
{
    int     counter;
    t_token *tmp;

    counter = 0;
    tmp = token;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (is_redir(tmp))
        {
            tmp = tmp->next;
            if (tmp)
                tmp = tmp->next;
            continue ;
        }
        if (tmp->type == TOKEN_WORD)
            counter++;
        tmp = tmp->next;
    }
    return (counter);
}

int open_file(int *fd_ptr, char *path, int flags)
{
    if (*fd_ptr > 2)
        close(*fd_ptr);
    *fd_ptr = open(path, flags, 0644);
    if (*fd_ptr == -1)
    {
        perror(path);
        return (1);
    }
    return (0);
}
```

---

### Free Functions

These must be symmetric to every allocation. Keep each function under 25 lines (42 norm):

```c
void    free_redirs(t_redir *redirs)
{
    t_redir *tmp;

    while (redirs)
    {
        tmp = redirs->next;
        free(redirs->file);
        free(redirs);
        redirs = tmp;
    }
}

void    free_cmd(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return ;
    if (cmd->cmd_args)
    {
        i = 0;
        while (cmd->cmd_args[i])
            free(cmd->cmd_args[i++]);
        free(cmd->cmd_args);
    }
    free(cmd->cmd_path);
    free_redirs(cmd->redirs);
    free(cmd);
}

void    free_cmds(t_cmd *cmds)
{
    t_cmd   *tmp;

    while (cmds)
    {
        tmp = cmds->next;
        free_cmd(cmds);
        cmds = tmp;
    }
}
```

---

## 42 Norm — Quick Checklist

| Rule | Status in current code |
|---|---|
| Max 25 lines per function | ⚠️ `count_words` and `handle_error` are close — watch when expanding |
| Max 5 functions per `.c` file | ✅ Current files respect this |
| No `for` loops — use `while` | ✅ All loops use `while` |
| No global variables (except signals) | ✅ None found |
| No block comments in final code | ⚠️ `redirects.c` has fully commented-out functions — remove before submission |
| 42 header in every file | ✅ Present in all files |
| Variable declarations at the top of the function | ✅ Respected |
| Every `malloc` return must be checked | ✅ Code checks returns |
| Every `malloc` must have a matching `free` | ⚠️ `free_cmd` / `free_cmds` not yet implemented |

---

## Integration with `t_mini`

The parser must be called after the lexer and before the executor. Example integration in the
main shell loop:

```c
/* Inside the minishell main loop */
mini->tokens = lexer(mini->input);
if (!mini->tokens)
{
    mini->exit_code = 2; /* bash returns exit code 2 for syntax errors */
    continue ;           /* return to prompt */
}
mini->cmd = parser(mini);
if (!mini->cmd)
{
    free_tokens(mini->tokens);
    mini->tokens = NULL;
    mini->exit_code = 2;
    continue ;
}
/* executor(mini); */
free_tokens(mini->tokens);
mini->tokens = NULL;
```

---

## Heredoc Handling

The heredoc (`<<`) requires special treatment: `t_redir.file` stores the **delimiter**, not a
filename. The body reading should happen in a dedicated `expand_heredocs` phase called before
execution, using `pipe()` + `write()` to feed data to the read-end fd:

```c
int handle_heredoc(t_redir *redir)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
        return (-1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, redir->file) == 0)
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd[1]);
        ft_putchar_fd('\n', fd[1]);
        free(line);
    }
    close(fd[1]);
    return (fd[0]); /* read-end fd passed to executor */
}
```

---

## Parser Completion Checklist

Work through these in order. Check each item off before moving to the next.

### Struct Fixes

- [ ] Fix `t_redir.type` — change from `t_token_type *` to `t_token_type` in `structs.h`
- [ ] Add `int expand` field to `t_redir` for heredoc expansion flag

### Syntax Validation

- [ ] Fix `validate_syntax` — return `0` for success (not `1`)
- [ ] Add null guard before `tmp->next->type` access
- [ ] Add redirect-without-filename check: `is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD)`
- [ ] Fix syntax error in `lexer.c` — replace `ft_printf` with `handle_error(ERR_SYNTAX, NULL, "newline")`

### Parser Core

- [ ] Implement `new_cmd` in `parser_utils.c`
- [ ] Fix `count_words` — pass `tmp` (not `token`) to `is_redir`; skip 2 tokens on redirect
- [ ] Implement `fill_args` in `parser.c`
- [ ] Implement `fill_redirs` in `parser.c`
- [ ] Implement `parse_cmd` in `parser.c`
- [ ] Implement `parser` entry point in `parser.c`

### Redirections

- [ ] Implement `add_redir` in `redirects.c`
- [ ] Remove all commented-out code blocks from `redirects.c`

### Memory Management

- [ ] Implement `free_redirs`
- [ ] Implement `free_cmd`
- [ ] Implement `free_cmds`
- [ ] Call `free_tokens` after the executor finishes (not just on error paths)
- [ ] Run `valgrind --leak-check=full` — zero leaks before moving on

### Testing the Parser

- [ ] `echo hello` → 1 cmd, 1 arg, no redirs
- [ ] `ls -la | grep foo` → 2 cmds, correct args per segment
- [ ] `cat < infile > outfile` → 1 cmd, 2 redirs, no args counted from filenames
- [ ] `echo hi >> log | wc -l` → 2 cmds, append redir on first
- [ ] `cat << EOF` → heredoc redir, delimiter = "EOF"
- [ ] `echo >` → syntax error (redirect without filename)
- [ ] `| ls` → syntax error (pipe at start)
- [ ] `ls |` → syntax error (pipe at end)
- [ ] `ls || cat` → syntax error (double pipe — not supported in minishell)

---

## What Comes After the Parser

Once all parser checklist items are done and valgrind is clean, the recommended development order
for the rest of the project is:

### Phase 1 — Executor (no pipes)

The executor takes `mini->cmd` and runs a single command. Start here before tackling pipes,
since it is easier to debug.

- Resolve `cmd->cmd_path` using `PATH` from the env list (walk `t_env`, split on `:`, `access()`)
- `fork()` + `execve(cmd->cmd_path, cmd->cmd_args, env_array)` in the child
- `waitpid()` in the parent; store exit status in `mini->exit_code`
- Apply redirections before `execve`: `open_file` + `dup2` for `<`, `>`, `>>`
- Handle heredoc: call `handle_heredoc` before fork, pass read-end fd via `dup2(fd, STDIN_FILENO)`

**Key tip:** Build a `char **env_array` helper that converts `t_env *` to the `char **envp`
format required by `execve`. Keep it in `env_utils.c`.

### Phase 2 — Pipelines

Extend the executor to handle `cmd->next` chains.

- For N commands, create N-1 `pipe()` pairs before any `fork()`
- Each child: `dup2` the correct read/write ends, then close **all** pipe fds before `execve`
- Parent: close all pipe fds after forking all children, then `waitpid` in a loop
- Store the exit code of the **last** command in the pipeline into `mini->exit_code`

**Key tip:** Closing unused pipe ends in every process is the most common source of hanging
pipelines. A helper `close_all_pipes(int **fds, int n)` keeps this manageable.

### Phase 3 — Builtins

Builtins must run in the **parent process** for single commands (so they can modify the shell
state) and in a **child process** when inside a pipeline (they cannot affect parent state there).

| Builtin | Notes |
|---|---|
| `echo` | Handle `-n` flag; only the first `-n` counts |
| `cd` | Update `PWD` and `OLDPWD` in `t_env`; use `ERR_NO_FILE` on failure |
| `pwd` | `getcwd()` or read `PWD` from env |
| `export` | Add/update key in `t_env`; print sorted list if no args |
| `unset` | Remove node from `t_env` |
| `env` | Print `key=value` for every node in `t_env` |
| `exit` | Validate numeric arg; call `exit(code)` |

**Key tip:** A dispatch helper `is_builtin(char *cmd)` + `run_builtin(t_cmd *, t_mini *)` keeps
the executor clean and avoids a long if-else chain.

### Phase 4 — Expansion

Variable expansion (`$VAR`, `$?`) must happen **after** parsing but **before** execution. Walk
`cmd->cmd_args` for every command and expand in place.

- `$?` → `ft_itoa(mini->exit_code)`
- `$VAR` → look up key in `t_env`, replace with value (empty string if not found)
- Expansion is **suppressed** inside single quotes
- Expansion is **active** inside double quotes
- Tilde `~` → value of `HOME` in env (only when it is the whole word or a prefix)

**Key tip:** Write `expand_token(char *value, t_mini *mini)` that returns a newly allocated
expanded string. Call it in a loop over `cmd->cmd_args` right after `parser()` returns.

### Phase 5 — Signal Handling

Signals must be set up correctly in three different contexts:

| Context | `SIGINT` | `SIGQUIT` |
|---|---|---|
| Interactive prompt (no child) | Print new prompt (`readline` reset) | Ignored |
| Child process running | Default (terminate child) | Default (core dump) |
| Heredoc input | Print new prompt | Ignored |

**Key tip:** Use a single global `int g_signal` (the only global allowed by the 42 norm). Set it
in the signal handler and check it after `waitpid` or `readline` returns.

### Phase 6 — Edge Cases & Final Polish

- Empty input (just spaces/newlines) → do nothing, no exit code change
- `ctrl-D` on empty line → print `exit`, call `exit(mini->exit_code)`
- Unclosed quotes → already caught by lexer; ensure exit code is `2`
- Multiple redirections on the same fd → last one wins; all files must still be opened
- Redirections on a builtin run in parent → apply with `dup2`, restore with `dup2(std_in/out, 0/1)` after
- Memory: free `mini->tokens` and `mini->cmd` at the end of every REPL iteration

---

## Recommended File Structure

```
minishell/
├── includes/
│   ├── shell.h          ← main header (all prototypes)
│   ├── structs.h        ← all typedef structs and enums
│   └── error_handler.h  ← t_error_type enum
├── src/
│   ├── main.c
│   ├── lexer/
│   │   ├── lexer.c
│   │   ├── lexer_inputs.c
│   │   ├── lexer_utils.c
│   │   └── tokens.c
│   ├── parser/
│   │   ├── parser.c        ← implement this
│   │   ├── parser_utils.c  ← fix and extend
│   │   ├── redirects.c     ← implement add_redir
│   │   └── syntax.c        ← fix return values
│   ├── executor/
│   │   ├── executor.c      ← Phase 1
│   │   ├── pipes.c         ← Phase 2
│   │   └── builtins.c      ← Phase 3
│   ├── expand/
│   │   └── expand.c        ← Phase 4
│   ├── signals/
│   │   └── signals.c       ← Phase 5
│   └── utils/
│       ├── error_utils.c
│       ├── env_utils.c
│       └── free_utils.c
└── Makefile
```

