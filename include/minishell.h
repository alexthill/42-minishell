/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:31 by athill            #+#    #+#             */
/*   Updated: 2024/04/22 16:12:19 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"

# define PROMPT	"minishell> "
# define TOO_MANY_ARGS		1
# define NUM_ARG_REQUIRED	2
# define SYNTAX_ERR			2
# define CMD_NOT_FOUND		127
# define MSG_TOO_MANY_ARGS		"too many arguments"
# define MSG_NUM_ARG_REQUIRED	"numeric argument required"
# define MSG_CMD_NOT_FOUND		"command not found"

typedef struct s_data
{
	char			*prog;
	char			**envp;
	char			**path;
	int				is_tty;
	int				exit;
	int				in_pipe;
	unsigned char	last_status;
	int				infile;
	int				outfile;
}	t_data;

// error.c
int		print_err(int code, char const *s, char const *msg);
int		print_errno(int is_err, char const *s);
int		print_err_full(char *prog, char const *extra, char const *msg);

// data.c
int		data_init(t_data *data, int argc, char **argv, char **envp);
int		data_free(t_data *data);

// path.c
char	**path_extract(char **envp);
char	*path_concat(char *p1, char *p2);

// exec.c
int		exec_line(t_data *data, char const *line);
int		exec_ast(t_data *data, t_ast *ast);
int		exec_pipe(t_data *data, t_ast *ast);

// exec_redirs.c
int		check_redirs(t_data *data, t_buffer *redirs);
int		exec_redirs(t_data *data);
int		reset_redirs(t_data *data, int status);

#endif
