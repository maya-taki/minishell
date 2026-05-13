# Minishell Parser — What Is Left to Implement

This document explains what still needs to be implemented or corrected in the current parser codebase, based on the latest parser files. It is written as a practical finishing guide so the parser can be completed safely and then integrated with the executor.

## Current Status

The parser already has the right high-level structure: `parser()` walks the token list, `parse_cmd()` builds one command node, `fill_args()` fills `cmd_args`, `fill_redirs()` walks redirections, and the free functions are already separated into a dedicated file.[cite:17][cite:15] The project is therefore no longer missing a parser architecture; it is mainly missing correctness fixes, return-value consistency, a few structural corrections, and safer integration with the rest of minishell.[cite:14][cite:16][cite:17]

## Main Problems Still Open

### 1. `t_redir.type` is still declared incorrectly

In `structs.h`, `t_redir.type` is still declared as `t_token_type *type` instead of `t_token_type type`.[cite:2] In the current parser, `redirect->type = type;` assigns an enum value into that field, which only makes sense if the field is a plain enum, not a pointer.[cite:17] This must be fixed before continuing, otherwise redirect comparisons in the executor will be unsafe or simply wrong.[cite:2][cite:17]

```c
typedef struct s_redir
{
    t_token_type    type;
    char            *file;
    struct s_redir  *next;
}   t_redir;
```

### 2. Return values are inconsistent across parser functions

`validate_syntax()` currently returns `0` in several syntax-error cases, `ERR_SYNTAX` for the double-pipe case, and `1` for success.[cite:14] At the same time, `validate_parser()` treats `!validate_syntax(mini->tokens)` as an error, while `parser()` incorrectly returns `0` when `validate_parser(mini)` is true, which inverts the intended control flow.[cite:17] `open_file()` has the same inversion problem: it returns `0` when `open()` fails and `1` on success, which is the opposite of the usual convention used by the other helpers.[cite:16]

To finish the parser cleanly, one convention must be adopted everywhere:

- return `0` for success and non-zero for error, or
- return `1` for success and `0` for failure.

The cleaner option for minishell is:

- `0` = success
- non-zero = error code

That matches error enums and makes propagation easier.[cite:14][cite:7]

### 3. `fill_redirs()` is using the wrong token as redirect filename

In the current implementation, `fill_redirs()` calls `add_redirs(tmp->type, tmp->value, cmd)` when it finds a redirect token.[cite:17] But `tmp->value` is the operator itself (`<`, `>`, `>>`, `<<`), not the target file; the file is in `tmp->next->value`.[cite:17][cite:10] This means redirections are currently being stored with the wrong string.

Current logic:

```c
if (!add_redirs(tmp->type, tmp->value, cmd))
    return (ERR_MALLOC);
```

Correct logic:

```c
if (!add_redirs(tmp->type, tmp->next->value, cmd))
    return (ERR_MALLOC);
```

### 4. `fill_redirs()` validates the wrong token type

Inside `fill_redirs()`, the current validation is:

```c
if (!tmp->next || tmp->type != TOKEN_WORD)
    return (ERR_SYNTAX);
```

This is wrong because it checks `tmp->type`, but `tmp` is already the redirect token.[cite:17] The correct condition is:

```c
if (!tmp->next || tmp->next->type != TOKEN_WORD)
    return (ERR_SYNTAX);
```

This matters because a redirect must always be followed by a filename token in the current design.[cite:14][cite:17]

### 5. `parser()` frees the wrong pointer on failure

If `parse_cmd(tmp)` fails, the current code does:

```c
free_all_cmds(cmd);
return (0);
```

At that point, `cmd` is either `NULL` or only the just-created node, while the already-built list is stored in `head`.[cite:17] The function should free `head`, not `cmd`, otherwise already-allocated commands leak on partial parser failure.[cite:15][cite:17]

Correct pattern:

```c
if (!cmd)
{
    free_all_cmds(head);
    return (NULL);
}
```

### 6. `parse_cmd()` does not free partially built command nodes on failure

`parse_cmd()` creates `cmd = new_cmd();`, then calls `fill_args()`, then `fill_redirs()`, but if one of those fails it returns `NULL` directly without freeing the partially allocated command.[cite:17][cite:16] That produces leaks in error paths.

It should do this instead:

```c
cmd = new_cmd();
if (!cmd)
    return (NULL);
if (fill_args(seg_start, cmd) != 0)
{
    free_single_cmd(cmd);
    return (NULL);
}
if (fill_redirs(seg_start, cmd) != 0)
{
    free_single_cmd(cmd);
    return (NULL);
}
return (cmd);
```

### 7. Error handling is not yet integrated with the parser layer

The parser still prints `ft_printf(RED"Unknown token\n"RST);` inside `validate_parser()`.[cite:17] The project already has a central error system with `handle_error()` and `error_msg()`.[cite:7] The parser should use that system instead of printing ad hoc messages, so all syntax failures behave the same way and write to `stderr` instead of stdout.[cite:7][cite:17]

A cleaner parser validation path is:

```c
if (validate_syntax(mini->tokens) != 0)
{
    handle_error(ERR_SYNTAX, NULL, "newline");
    return (1);
}
return (0);
```

## Recommended Final Design

The safest final parser design is to keep `parser()` simple and let each helper do only one thing.[cite:16][cite:17] The command-building flow should be:

1. Validate parser input.
2. Validate token syntax.
3. Start at the first token of a pipeline segment.
4. Create one `t_cmd`.
5. Fill arguments.
6. Fill redirections.
7. Append command to the linked list.
8. Advance until the next pipe.
9. Repeat until the token list ends.[cite:14][cite:17]

### Final control-flow model

```c
t_cmd   *parser(t_mini *mini)
{
    t_token *tmp;
    t_cmd   *head;
    t_cmd   *cmd;
    t_cmd   *last;

    if (!mini || !mini->tokens)
        return (NULL);
    if (validate_syntax(mini->tokens) != 0)
    {
        handle_error(ERR_SYNTAX, NULL, "newline");
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
            free_all_cmds(head);
            return (NULL);
        }
        if (!head)
            head = cmd;
        else
            last->next = cmd;
        last = cmd;
        while (tmp && tmp->type != TOKEN_PIPE)
            tmp = tmp->next;
        if (tmp)
            tmp = tmp->next;
    }
    return (head);
}
```

## Concrete Fixes File by File

### `syntax.c`

`validate_syntax()` is close, but it still mixes success/failure conventions.[cite:14] It should consistently return `ERR_SYNTAX` on syntax failure and `0` on success.[cite:14][cite:7]

Suggested version:

```c
static int  is_pipe_last(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (!tmp->next && tmp->type == TOKEN_PIPE)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int validate_syntax(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    if (!tmp)
        return (0);
    if (tmp->type == TOKEN_PIPE)
        return (ERR_SYNTAX);
    if (is_pipe_last(tmp))
        return (ERR_SYNTAX);
    while (tmp)
    {
        if (is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD))
            return (ERR_SYNTAX);
        if (tmp->type == TOKEN_PIPE && tmp->next
            && tmp->next->type == TOKEN_PIPE)
            return (ERR_SYNTAX);
        tmp = tmp->next;
    }
    return (0);
}
```

### `parser_utils.c`

`new_cmd()` and `count_words()` are structurally fine, but `open_file()` still has inverted return values.[cite:16] It should return non-zero on failure and `0` on success, especially if it will be reused by the executor.[cite:16]

Correct version:

```c
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

### `parser.c`

This file contains most of what is left.[cite:17] The structure is already usable, but it needs five direct fixes:

- `fill_redirs()` must check `tmp->next->type`, not `tmp->type`.[cite:17]
- `fill_redirs()` must pass `tmp->next->value` as the redirect filename.[cite:17]
- `parse_cmd()` must free `cmd` on failure.[cite:17][cite:15]
- `validate_parser()` should be removed or simplified; right now it inverts logic and duplicates validation.[cite:17]
- `parser()` must free `head` on failure and return `NULL`, not `0`, for pointer-returning functions.[cite:17]

A corrected implementation is:

```c
static int  add_args(t_token *seg_start, t_cmd *cmd)
{
    t_token *tmp;
    int     i;

    i = 0;
    tmp = seg_start;
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
            cmd->cmd_args[i] = ft_strdup(tmp->value);
            if (!cmd->cmd_args[i])
                return (1);
            i++;
        }
        tmp = tmp->next;
    }
    cmd->cmd_args[i] = NULL;
    return (0);
}

int fill_args(t_token *seg_start, t_cmd *cmd)
{
    cmd->cmd_args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
    if (!cmd->cmd_args)
        return (1);
    return (add_args(seg_start, cmd));
}

int fill_redirs(t_token *seg_start, t_cmd *cmd)
{
    t_token *tmp;

    tmp = seg_start;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if (is_redir(tmp))
        {
            if (!tmp->next || tmp->next->type != TOKEN_WORD)
                return (ERR_SYNTAX);
            if (add_redirs(tmp->type, tmp->next->value, cmd) != 0)
                return (ERR_MALLOC);
            tmp = tmp->next->next;
            continue ;
        }
        tmp = tmp->next;
    }
    return (0);
}

t_cmd   *parse_cmd(t_token *seg_start)
{
    t_cmd   *cmd;

    cmd = new_cmd();
    if (!cmd)
        return (NULL);
    if (fill_args(seg_start, cmd) != 0)
    {
        free_single_cmd(cmd);
        return (NULL);
    }
    if (fill_redirs(seg_start, cmd) != 0)
    {
        free_single_cmd(cmd);
        return (NULL);
    }
    return (cmd);
}
```

### `parser_frees.c`

The free functions are basically complete and already correctly structured for the parser layer.[cite:15] The main thing left here is naming consistency: `free_redir()` would be clearer as `free_redirs()`, since it frees a whole list, not one node.[cite:15] That is optional, but it makes the API easier to read.

### `redirects.c`

This file still contains only `is_redir()` and several blocks of old commented code.[cite:18] Those commented-out redirect handlers should be removed now, because they are no longer part of the parser design and will only make future executor work more confusing.[cite:18] The parser no longer needs redirect execution handlers here; it only needs redirection classification plus node creation in the parser layer.[cite:17][cite:18]

## Step-by-Step Finish Plan

### Phase 1 — Correct data structures

- [ ] Fix `t_redir.type` in `structs.h` from pointer to plain enum.[cite:2]
- [ ] Recompile and fix all compiler errors caused by that type correction.[cite:2]

### Phase 2 — Unify return values

- [ ] Make `validate_syntax()` return `0` on success and `ERR_SYNTAX` on failure.[cite:14]
- [ ] Make `open_file()` return `1` on failure and `0` on success.[cite:16]
- [ ] Make `fill_args()` return `0` on success and non-zero on failure.[cite:17]
- [ ] Make `fill_redirs()` return `0` on success and non-zero on failure.[cite:17]
- [ ] Make `parse_cmd()` return `NULL` on failure and a valid pointer on success.[cite:17]
- [ ] Make `parser()` return `NULL` on failure and `t_cmd *` on success.[cite:17]

### Phase 3 — Correct command content

- [ ] Change `fill_redirs()` to validate `tmp->next->type`, not `tmp->type`.[cite:17]
- [ ] Change `fill_redirs()` to store `tmp->next->value` as the redirect target.[cite:17]
- [ ] Keep `fill_args()` skipping both redirect tokens and redirect filenames so filenames do not end up in `cmd_args`.[cite:16][cite:17]

### Phase 4 — Fix cleanup paths

- [ ] In `parse_cmd()`, free `cmd` when `fill_args()` fails.[cite:17][cite:15]
- [ ] In `parse_cmd()`, free `cmd` when `fill_redirs()` fails.[cite:17][cite:15]
- [ ] In `parser()`, free `head` when one segment fails to parse.[cite:17][cite:15]

### Phase 5 — Integrate error handling

- [ ] Replace `ft_printf("Unknown token")` with `handle_error(ERR_SYNTAX, NULL, "newline")` or another precise context string.[cite:17][cite:7]
- [ ] Keep parser errors on `stderr`, not stdout.[cite:7]

### Phase 6 — Remove dead code

- [ ] Remove old commented-out redirect handlers from `redirects.c`.[cite:18]
- [ ] Remove redundant forward declarations that already belong in headers.[cite:16][cite:17][cite:15]

## Parser Validation Checklist

Use this checklist before moving to the executor.

### Basic commands

- [ ] `ls`
- [ ] `echo hello`
- [ ] `echo hello world`

Expected result: one `t_cmd`, correct `cmd_args`, no redirections.[cite:17]

### Pipes

- [ ] `ls | wc`
- [ ] `ls -l | grep minishell | wc -l`

Expected result: one `t_cmd` node per segment, linked through `next`, each segment keeping only its own arguments.[cite:17][cite:16]

### Redirections

- [ ] `cat < infile`
- [ ] `echo hi > outfile`
- [ ] `echo hi >> logfile`
- [ ] `cat << EOF`

Expected result: redirect nodes stored in `cmd->redirs`, filenames or delimiters copied from `tmp->next->value`, not operator tokens.[cite:17]

### Syntax errors

- [ ] `| ls`
- [ ] `ls |`
- [ ] `ls || wc`
- [ ] `echo >`
- [ ] `cat < | wc`

Expected result: parser stops, syntax error is reported, and no leaked command list remains.[cite:14][cite:15][cite:17]

### Memory safety

- [ ] Run valgrind on successful parse cases.
- [ ] Run valgrind on syntax error cases.
- [ ] Run valgrind on forced malloc-failure simulations if available.

Expected result: no leaks from `cmd_args`, `cmd_path`, `redirs`, or partial command lists.[cite:15][cite:17]

## After the Parser

Once the parser is stable, the next step is not to add more parser features but to connect it cleanly to execution. The parser should hand off a reliable `t_cmd` list that the executor can walk without caring about raw tokens anymore.[cite:2][cite:17]

Recommended next order:

1. Implement single-command execution using `cmd_args` and `cmd_path`.[cite:2]
2. Implement redirection application from `cmd->redirs` before `execve`.[cite:2]
3. Implement pipelines using the `next` chain in `t_cmd`.[cite:2]
4. Only then add polish such as heredoc preprocessing and expansion handling.[cite:2]

That order keeps responsibilities clean: lexer builds tokens, parser builds commands, executor runs commands.[cite:2][cite:17]
