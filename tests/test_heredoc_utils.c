/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:46:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/03 21:19:06 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/shell.h"

/* Forward declarations from heredoc.c */
int		is_single_quoted(char *delimiter);
char	*remove_quotes(char *delimiter);
void	write_lines(char *line, int fd);

/* Test helper function */
void	print_test_result(const char *test_name, int passed)
{
	printf("[%s] %s\n", passed ? "✓" : "✗", test_name);
}

/* ==================== is_single_quoted tests ==================== */
void	test_is_single_quoted(void)
{
	printf("\n=== Testing is_single_quoted ===\n");
	
	char *test1 = "EOF";
	int result1 = is_single_quoted(test1);
	print_test_result("is_single_quoted('EOF') should return 1", result1 == 1);
	
	char *test2 = "'EOF'";
	int result2 = is_single_quoted(test2);
	print_test_result("is_single_quoted(\"'EOF'\") should return 0", result2 == 0);
	
	char *test3 = "\"EOF\"";
	int result3 = is_single_quoted(test3);
	print_test_result("is_single_quoted(\"\\\"EOF\\\"\") should return 0", result3 == 0);
	
	char *test4 = NULL;
	int result4 = is_single_quoted(test4);
	print_test_result("is_single_quoted(NULL) should return 1", result4 == 1);
	
	char *test5 = "";
	int result5 = is_single_quoted(test5);
	print_test_result("is_single_quoted(\"\") should return 1", result5 == 1);
	
	char *test6 = "'";
	int result6 = is_single_quoted(test6);
	print_test_result("is_single_quoted(\"'\") should return 0", result6 == 0);
}

/* ==================== remove_quotes tests ==================== */
void	test_remove_quotes(void)
{
	printf("\n=== Testing remove_quotes ===\n");
	
	char test1[] = "'EOF'";
	char *result1 = remove_quotes(test1);
	print_test_result("remove_quotes(\"'EOF'\") returns 'EOF'", 
					  strcmp(result1, "EOF") == 0);
	printf("  Result: '%s'\n", result1);
	if (result1 != test1)
		free(result1);
	
	char test2[] = "\"DELIM\"";
	char *result2 = remove_quotes(test2);
	print_test_result("remove_quotes(\"\\\"DELIM\\\"\") returns 'DELIM'", 
					  strcmp(result2, "DELIM") == 0);
	printf("  Result: '%s'\n", result2);
	if (result2 != test2)
		free(result2);
	
	char test3[] = "EOF";
	char *result3 = remove_quotes(test3);
	print_test_result("remove_quotes('EOF') returns copy of 'EOF'", 
					  strcmp(result3, "EOF") == 0);
	printf("  Result: '%s'\n", result3);
	if (result3 != test3)
		free(result3);
	
	char test4[] = "AB";
	char *result4 = remove_quotes(test4);
	print_test_result("remove_quotes('AB') returns copy (length == 2, not <)", 
					  strcmp(result4, "AB") == 0 && result4 != test4);
	printf("  Result: '%s' (different pointer)\n", result4);
	if (result4 != test4)
		free(result4);
	
	char test5[] = "";
	char *result5 = remove_quotes(test5);
	print_test_result("remove_quotes('') returns original (length < 2)", 
					  result5 == test5);
	printf("  Result: '%s' (same pointer)\n", result5);
	
	char test6[] = "'test'";
	char *result6 = remove_quotes(test6);
	print_test_result("remove_quotes(\"'test'\") returns 'test'", 
					  strcmp(result6, "test") == 0);
	printf("  Result: '%s'\n", result6);
	if (result6 != test6)
		free(result6);
	
	char test7[] = "\"hello\"";
	char *result7 = remove_quotes(test7);
	print_test_result("remove_quotes(\"\\\"hello\\\"\") returns 'hello'", 
					  strcmp(result7, "hello") == 0);
	printf("  Result: '%s'\n", result7);
	if (result7 != test7)
		free(result7);
	
	char test8[] = "unquoted";
	char *result8 = remove_quotes(test8);
	print_test_result("remove_quotes('unquoted') returns copy (different pointer)", 
					  strcmp(result8, "unquoted") == 0 && result8 != test8);
	printf("  Result: '%s' (different pointer)\n", result8);
	if (result8 != test8)
		free(result8);
}

/* ==================== write_lines tests ==================== */
void	test_write_lines(void)
{
	printf("\n=== Testing write_lines ===\n");
	
	const char *test_file = "/tmp/test_write_lines.txt";
	
	/* Test 1: Single line write */
	int fd = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("✗ Failed to open test file\n");
		return ;
	}
	write_lines("Hello", fd);
	close(fd);
	
	FILE *f = fopen(test_file, "r");
	char buffer[100] = {0};
	fgets(buffer, sizeof(buffer), f);
	fclose(f);
	print_test_result("write_lines('Hello', fd) writes 'Hello\\n'", 
					  strcmp(buffer, "Hello\n") == 0);
	printf("  Result: '%s'\n", buffer);
	
	/* Test 2: Multiple lines */
	fd = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_lines("Line1", fd);
	write_lines("Line2", fd);
	write_lines("Line3", fd);
	close(fd);
	
	f = fopen(test_file, "r");
	fgets(buffer, sizeof(buffer), f);
	char buffer2[100] = {0};
	fgets(buffer2, sizeof(buffer2), f);
	char buffer3[100] = {0};
	fgets(buffer3, sizeof(buffer3), f);
	fclose(f);
	print_test_result("write_lines writes 3 lines correctly", 
					  strcmp(buffer, "Line1\n") == 0 && 
					  strcmp(buffer2, "Line2\n") == 0 && 
					  strcmp(buffer3, "Line3\n") == 0);
	
	/* Test 3: Empty string */
	fd = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_lines("", fd);
	close(fd);
	
	f = fopen(test_file, "r");
	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), f);
	fclose(f);
	print_test_result("write_lines('', fd) writes newline only", 
					  strcmp(buffer, "\n") == 0);
	printf("  Result: newline written\n");
	
	/* Cleanup */
	unlink(test_file);
}

int	main(void)
{
	printf("╔════════════════════════════════════════════════════╗\n");
	printf("║  Testing heredoc utility functions                ║\n");
	printf("╚════════════════════════════════════════════════════╝\n");
	
	test_is_single_quoted();
	test_remove_quotes();
	test_write_lines();
	
	printf("\n╔════════════════════════════════════════════════════╗\n");
	printf("║  All tests completed                              ║\n");
	printf("╚════════════════════════════════════════════════════╝\n");
	
	return (0);
}
