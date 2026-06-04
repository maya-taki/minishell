#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../includes/shell.h"

int open_file(int *fd_ptr, char *path, int flags)
{
	if (*fd_ptr > 2)
		close(*fd_ptr);
	*fd_ptr = open(path, flags, 0644);
	if (*fd_ptr == -1)
		return (1);
	return (0);
}

static t_token *new_token(t_token_type type, const char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

static void free_token_chain(t_token *token)
{
	t_token *next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

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

static int assert_int(int actual, int expected, const char *name)
{
	if (actual != expected)
	{
		printf("FAIL: %s - expected %d, got %d\n", name, expected, actual);
		return (1);
	}
	printf("PASS: %s\n", name);
	return (0);
}

static int assert_string(const char *actual, const char *expected, const char *name)
{
	if (!actual || !expected)
	{
		if (actual != expected)
		{
			printf("FAIL: %s - unexpected null\n", name);
			return (1);
		}
		printf("PASS: %s\n", name);
		return (0);
	}
	if (strcmp(actual, expected) != 0)
	{
		printf("FAIL: %s\n  expected: '%s'\n  actual:   '%s'\n", name, expected, actual);
		return (1);
	}
	printf("PASS: %s\n", name);
	return (0);
}

static int read_file_content(const char *path, char *buffer, size_t size)
{
	int fd;
	ssize_t bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	bytes = read(fd, buffer, size - 1);
	close(fd);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	return (int)bytes;
}

int main(void)
{
	t_shell shell;
	t_token *redir;
	t_token *file_token;
	int failures;
	char buffer[128];

	init_test_shell(&shell);
	failures = 0;

	unlink("tests/test_redirects_out.txt");
	redir = new_token(TOKEN_REDIR_OUT, "tests/test_redirects_out.txt");
	file_token = new_token(TOKEN_WORD, "tests/test_redirects_out.txt");
	redir->next = file_token;
	failures += assert_int(handle_redir(redir, NULL, &shell), 1, "redirect output success");
	failures += assert_int(shell.std_out > 0, 1, "output fd opened");
	write(shell.std_out, "out\n", 4);
	close(shell.std_out);
	shell.std_out = -1;
	failures += assert_int(read_file_content("tests/test_redirects_out.txt", buffer, sizeof(buffer)), 4, "output file length");
	failures += assert_string(buffer, "out\n", "output file content");
	free_token_chain(redir);

	unlink("tests/test_redirects_append.txt");
	int create_fd = open("tests/test_redirects_append.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(create_fd, "abc", 3);
	close(create_fd);
	init_test_shell(&shell);
	redir = new_token(TOKEN_REDIR_APPEND, "tests/test_redirects_append.txt");
	file_token = new_token(TOKEN_WORD, "tests/test_redirects_append.txt");
	redir->next = file_token;
	failures += assert_int(handle_redir(redir, NULL, &shell), 1, "redirect append success");
	failures += assert_int(shell.std_out > 0, 1, "append fd opened");
	write(shell.std_out, "xyz", 3);
	close(shell.std_out);
	shell.std_out = -1;
	failures += assert_int(read_file_content("tests/test_redirects_append.txt", buffer, sizeof(buffer)), 6, "append file length");
	failures += assert_string(buffer, "abcxyz", "append file content");
	free_token_chain(redir);

	unlink("tests/test_redirects_in.txt");
	create_fd = open("tests/test_redirects_in.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(create_fd, "readme", 6);
	close(create_fd);
	init_test_shell(&shell);
	redir = new_token(TOKEN_REDIR_IN, "tests/test_redirects_in.txt");
	file_token = new_token(TOKEN_WORD, "tests/test_redirects_in.txt");
	redir->next = file_token;
	failures += assert_int(handle_redir(redir, NULL, &shell), 1, "redirect input success");
	failures += assert_int(shell.std_in > 0, 1, "input fd opened");
	read(shell.std_in, buffer, 6);
	buffer[6] = '\0';
	close(shell.std_in);
	shell.std_in = -1;
	failures += assert_string(buffer, "readme", "input file content");
	free_token_chain(redir);

	unlink("tests/test_redirects_out.txt");
	unlink("tests/test_redirects_append.txt");
	unlink("tests/test_redirects_in.txt");
	return (failures != 0);
}
