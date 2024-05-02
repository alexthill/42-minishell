/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:31 by athill            #+#    #+#             */
/*   Updated: 2024/05/02 14:22:05 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "libft.h"

# define PROMPT			"minishell> "
# define PROMPT_HEREDOC	"> "
# define TOO_MANY_ARGS		1
# define NUM_ARG_REQUIRED	2
# define SYNTAX_ERR			2
# define CMD_NOT_FOUND		127
# define MSG_TOO_MANY_ARGS		"too many arguments"
# define MSG_NUM_ARG_REQUIRED	"numeric argument required"
# define MSG_CMD_NOT_FOUND		"command not found"
# define MSG_CD_ERR				"No such file or directory"

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
	char			**path;
	int				is_tty;
	int				exit;
	int				in_pipe;
	unsigned char	last_status;
	int				infile;
	int				outfile;
	t_env			*env;
	int				fd_in;
}	t_data;

// main.c
char	*get_line(t_data *data, char const *prompt);

// error.c
int		print_err(int code, char const *s, char const *msg);
int		print_errno(int is_err, char const *s);
int		print_err_full(char *prog, char const *extra, char const *msg);

// data.c
int		data_init(t_data *data, int argc, char **argv, char **envp);
int		data_free(t_data *data);
int		data_set_status(t_data *data, int status);

// path.c
char	**path_extract(char **envp);
char	*path_concat(char *p1, char *p2);

// exec.c
int		exec_line(t_data *data, char const *line);
int		exec_ast(t_data *data, t_ast *ast);

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
char	*get_env_var(t_data *data, char *name);
int		set_env_var(t_data *data, char *name, char *value);
int		modify_or_add_env_variable(t_data *data, char *name, char *value);
int		env_to_envp(t_data *data, char ***envp);

//builtins utils
int		update_oldpwd(t_data *data, char **args);
int		update_pwd(t_data *data, char **args);
int		sort_export(t_data *data);
int		print_export(t_data *data);
int		print_env(t_data *data);

//utils 
void	ft_lstadd_front2(t_env **lst, t_env *new);
t_env	*ft_lstnew2(void *name, void *value);
char	**ft_split2(const char *s, char c);
void	swap_nodes(t_env *node);

//signal
void	signal_init(void);
void	signal_handler(int sign_num);

#endif
