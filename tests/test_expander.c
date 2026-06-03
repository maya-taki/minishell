#include <stdio.h>
#include <string.h>
#include "../includes/shell.h"

char *expand_word(const char *src, t_shell *shell);

static void init_test_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->input = NULL;
	shell->prompt_str = NULL;
	shell->exit_code = 0;
	shell->std_in = -1;
	shell->std_out = -1;
}

static int add_env(t_shell *shell, const char *key, const char *value)
{
	t_env *node;

	node = env_new((char *)key, (char *)value);
	if (!node)
		return (1);
	env_add_back(&shell->env, node);
	return (0);
}

static int assert_string(const char *actual, const char *expected, const char *name)
{
	if ((actual == NULL && expected != NULL) || (actual != NULL && expected == NULL))
	{
		printf("FAIL: %s - unexpected null\n", name);
		return (1);
	}
	if (actual && expected && strcmp(actual, expected) != 0)
	{
		printf("FAIL: %s\n  expected: '%s'\n  actual:   '%s'\n", name, expected, actual);
		return (1);
	}
	printf("PASS: %s\n", name);
	return (0);
}

static int run_case(const char *input, int exit_code, t_shell *shell, const char *expected, const char *name)
{
	char *result;
	int  failed;

	shell->exit_code = exit_code;
	result = expand_word(input, shell);
	failed = assert_string(result, expected, name);
	free(result);
	return (failed);
}

int main(void)
{
	t_shell shell;
	int failures;

	init_test_shell(&shell);
	if (add_env(&shell, "HOME", "/home/test") != 0)
		return (1);
	if (add_env(&shell, "USER", "tester") != 0)
	{
		free_shell(&shell);
		return (1);
	}

	failures = 0;
	failures += run_case("$HOME/bin", 0, &shell, "/home/test/bin", "expand basic env var");
	failures += run_case("echo $? done", 127, &shell, "echo 127 done", "expand exit code");
	failures += run_case("foo '$HOME' bar", 0, &shell, "foo $HOME bar", "preserve single quotes");
	failures += run_case("foo \"$HOME\" bar", 0, &shell, "foo /home/test bar", "expand inside double quotes");
	failures += run_case("multiple $USER and $HOME", 0, &shell, "multiple tester and /home/test", "expand multiple env vars");
	failures += run_case("trailing dollar$", 0, &shell, "trailing dollar$", "preserve trailing dollar sign");
	failures += run_case("missing $NOPE var", 0, &shell, "missing  var", "missing env variable becomes empty");
	failures += run_case("underscore $USER_NAME", 0, &shell, "underscore ", "missing underscore var is empty");

	free_shell(&shell);
	return (failures != 0);
}
