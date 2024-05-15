/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:31 by athill            #+#    #+#             */
/*   Updated: 2024/05/15 09:48:54 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "buffer.h"
# include "libft.h"

# define PROMPT			"minishell> "
# define PROMPT_HEREDOC	"> "
# define TOO_MANY_ARGS		1
# define NUM_ARG_REQUIRED	2
# define SYNTAX_ERR			2
# define CMD_NOT_FOUND		127
# define INTERRUPTED		130
# define FILE_NOT_FOUND		130
# define MSG_TOO_MANY_ARGS		"too many arguments"
# define MSG_NUM_ARG_REQUIRED	"numeric argument required"
# define MSG_CMD_NOT_FOUND		"command not found"
# define MSG_FILE_NOT_FOUND		"No such file or directory"
# define MSG_EXPORT_ERR			"not a valid identifier"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			*prog;
	char			**envp;
	int				is_tty;
	int				exit;
	int				in_pipe;
	unsigned char	last_status;
	int				infile;
	int				outfile;
	t_env			*env;
	int				fd_in;
	int				signum;
	t_buffer		tokens;
	t_buffer		ast_stack;
}	t_data;

// main.c
void	set_signum(int signum);
int		get_signum(void);
char	*get_line(t_data *data, char const *prompt);

// error.c
int		print_err(int code, char const *s, char const *msg);
int		print_errno(int is_err, char const *s);
int		print_err_full(char *prog, char const *extra, char const *msg);
int		print_err_more(t_data *prog, char *ext, char *ext2, char *msg);
int		print_export_err(t_data *prog, char const *msg);

// data.c
int		data_init(t_data *data, int argc, char **argv, char **envp);
int		data_free(t_data *data);
int		data_set_status(t_data *data, int status);

// path.c
int		path_is_empty(t_data *data);
char	**path_get(t_data *data);
char	*path_concat(char const *p1, char const *p2);

// exec.c
int		exec_line(t_data *data, char *line);
int		exec_ast(t_data *data, t_ast *ast);
// exec_leaf.c
int		exec_leaf(t_data *data, char **args);
// exec_pipe.c
int		exec_pipe(t_data *data, t_ast *ast);
// exec_redirs.c
int		check_redirs(t_data *data, t_buffer *redirs);
int		exec_redirs(t_data *data);
void	reset_redirs(t_data *data);

// expand_string.c
void	expand_string(t_data *data, char const *s, t_buffer *buf);
char	*expand_string2(t_data *data, char const *s);
char	**expand_args(t_data *data, size_t argc, char **argv);

// glob.c
int		glob_arg(char *arg, t_buffer *buf);

// ft_sort_str_tab.c
void	ft_sort_str_tab(char **tab, size_t size);

//env var manipulations
t_env	*env_var_extract(char **envp);
char	*get_env_var(t_data *data, char const *name);
int		env_to_envp(t_data *data, char ***envp);
void	modify_or_add_env_variable(t_data *data, char *name, char *value);

//utils 
void	ft_lstadd_front2(t_env **lst, t_env *new);
t_env	*ft_lstnew2(void *name, void *value);
char	**ft_split2(const char *s, char c);
int		is_valid_char_exp(t_data *data, char **args);

// signal.c
void	signal_init(int init, int for_readline);
void	signal_default(void);

#endif
