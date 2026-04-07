#ifndef SHELL_H
# define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

struct t_token;

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VAR,
	AND,
	OR,
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}	t_token;



#endif