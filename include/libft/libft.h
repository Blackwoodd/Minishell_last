/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:46:12 by nsalhi            #+#    #+#             */
/*   Updated: 2023/06/07 17:08:17 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_gnl
{
	char		*buf;
	char		*line;
	int			r_read;
}	t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isspace(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_putstr(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(const char *s, const char *to_find);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_split_set(char *str, char *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int d);
int		ft_setinstr(char *str, char *set);
char	*ft_realloc_str(char *str, int size);
int		ft_str_arr_len(char **arr);
char	**ft_add_str_to_tab(char ***arr, int pos, char *new);
char	**ft_str_arr_dup(char **arr);
char	*ft_append(char **dst, char *src);
char	*ft_strstrjoin(char *s1, char *s2, char *divider);
void	ft_free_single_str(char ***arr, int i);
void	ft_free_str_array(char ***arr);
char	**ft_realloc_str_arr(char **arr, int size);
void	*ft_free(void **p);
char	*ft_append_len_div(char **dst, char *src, int len, char *div);
char	**ft_sort_str_arr(char *unsorted[]);
char	**ft_str_arr_realloc(char *array[], size_t size);
int		ft_perror(int exit_status, char *msg);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_putlhex_fd(int fd, unsigned long long nbr);
int		ft_putuhex_fd(int fd, unsigned long long nbr);
int		ft_putptr_fd(int fd, void *ptr);
int		ft_putunbr_fd(int fd, unsigned int nbr);
int		ft_putlnbr_fd(int fd, long nbr);
char	*ft_htoa(unsigned long long dec, int uppcase);
int		ft_putlnbr(long nbr);
int		ft_issign(char c);
long	ft_atol(const char *str);

// Bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strlen_mod(char *str);

int		ft_findnl(char *stash);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(const char *s1, const char *s2);
char	*ft_strdup_gnl(char *s);
char	*get_next_line(int fd, int boolean);

void	*ft_free_split(char **split);
void	ft_free_str(char **str);
int		ft_setinstr(char *str, char *set);
int		ft_strclen(char *str, char c);

#endif
