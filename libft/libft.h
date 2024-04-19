/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:33:47 by athill            #+#    #+#             */
/*   Updated: 2024/02/22 09:16:30 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(char const *nptr);
long	ft_atol_checked(char const *str, int *error);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char const *c, int fd);
void	ft_putstr_fd(char const *c, int fd);

char	**ft_split(char const *s, char c);
void	ft_str_array_free(char **array);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char const *s1, char const *s2);
char	*ft_strdup(char const *s);
int		ft_streq(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, char const *src, size_t size);
size_t	ft_strlcpy(char *dest, char const *src, size_t size);
size_t	ft_strlen(char const *s);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr2(char const *src, size_t start, size_t end);

int		ft_tolower(int c);
int		ft_toupper(int c);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
