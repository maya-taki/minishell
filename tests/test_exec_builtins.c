#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/shell.h"

static void init_test_shell(t_shell *shell)
{
    shell->env = NULL;
    shell->cmd = NULL;
    shell->tokens = NULL;
    shell->input = NULL;
    shell->prompt_str = NULL;
    shell->exit_code = 0;
    shell->exit_shell = 0;
    shell->std_in = -1;
    shell->std_out = -1;
}

static t_cmd *make_cmd(char **args, t_builtin builtin)
{
    t_cmd *cmd;
    int i;

    cmd = init_cmd();
    if (!cmd)
        return (NULL);
    i = 0;
    while (args && args[i])
        i++;
    cmd->args = malloc(sizeof(char *) * (i + 1));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    i = 0;
    while (args && args[i])
    {
        cmd->args[i] = ft_strdup(args[i]);
        i++;
    }
    cmd->args[i] = NULL;
    cmd->builtin = builtin;
    return (cmd);
}

static int assert_int(int actual, int expected, const char *name)
{
    if (actual != expected)
    {
        printf("FAIL: %s - expected %d but got %d\n", name, expected, actual);
        return (1);
    }
    printf("PASS: %s\n", name);
    return (0);
}

static int assert_str_null(const char *s, const char *name)
{
    if (s)
    {
        printf("FAIL: %s - expected NULL but got '%s'\n", name, s);
        return (1);
    }
    printf("PASS: %s\n", name);
    return (0);
}

static int assert_str_eq(const char *s, const char *exp, const char *name)
{
    if ((s == NULL && exp != NULL) || (s != NULL && exp == NULL))
    {
        printf("FAIL: %s - unexpected null\n", name);
        return (1);
    }
    if (s && exp && strcmp(s, exp) != 0)
    {
        printf("FAIL: %s - expected '%s' but got '%s'\n", name, exp, s);
        return (1);
    }
    printf("PASS: %s\n", name);
    return (0);
}

int main(void)
{
    t_shell shell;
    t_cmd *cmd;
    char *envp[] = {"HOME=/tmp", "USER=tester", NULL};
    int failures = 0;

    init_test_shell(&shell);
    if (!init_shell(&shell, envp))
    {
        printf("Failed to init shell for tests\n");
        return (1);
    }

    /* echo */
    char *echo_args[] = {"echo", "hello", NULL};
    cmd = make_cmd(echo_args, ECHO);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "echo returns 0");
    failures += assert_int(shell.exit_code, 0, "echo sets exit_code 0");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* pwd */
    char *pwd_args[] = {"pwd", NULL};
    cmd = make_cmd(pwd_args, PWD);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "pwd returns 0");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* cd success (to current dir '.') */
    char *cd_ok_args[] = {"cd", ".", NULL};
    cmd = make_cmd(cd_ok_args, CD);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "cd . returns 0");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* cd fail */
    char *cd_bad_args[] = {"cd", "/this_path_should_not_exist_12345", NULL};
    cmd = make_cmd(cd_bad_args, CD);
    shell.cmd = cmd;
    failures += (execute(&shell) == 0) ? (assert_int(1, 0, "cd nonexistent should fail")) : 0;
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* export */
    char *exp_args[] = {"export", "FOO=bar", NULL};
    cmd = make_cmd(exp_args, EXPORT);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "export returns 0");
    failures += assert_str_eq(get_env_var(shell.env, "FOO"), "bar", "export sets FOO=bar");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* unset */
    set_env_var(&shell.env, "TOREMOVE", "1");
    char *unset_args[] = {"unset", "TOREMOVE", NULL};
    cmd = make_cmd(unset_args, UNSET);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "unset returns 0");
    failures += assert_str_null(get_env_var(shell.env, "TOREMOVE"), "unset removed TOREMOVE");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* env */
    char *env_args[] = {"env", NULL};
    cmd = make_cmd(env_args, ENV);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 0, "env returns 0");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    /* exit */
    shell.exit_code = 5;
    char *exit_args[] = {"exit", NULL};
    cmd = make_cmd(exit_args, EXIT);
    shell.cmd = cmd;
    failures += assert_int(execute(&shell), 5, "exit returns current exit_code");
    failures += assert_int(shell.exit_shell, 1, "exit sets exit_shell flag");
    free_single_cmd(cmd);
    shell.cmd = NULL;

    free_shell(&shell);
    return (failures != 0);
}
