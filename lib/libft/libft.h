/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:33:08 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/27 17:25:14 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# define LL 922337203685477580

/*
** LIBC.
*/

void				*ft_memset(void	*b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src,
					size_t n);
void				*ft_memccpy(void *dst, const void *src,
					int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2,
					size_t n);
size_t				ft_strlcat(char *dst, const char *src,
					size_t dst_size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** ADDITIONAL.
*/

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t len);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** EXTRA.
*/

void				ft_swap(int *a, int *b);
int					ft_is_prime(int nb);
int					ft_recursive_power(int nb, int power);
int					ft_is_sort(int *tab, int length, int (*f)(int, int));
int					ft_sqrt(int nb);
int					ft_elems(char **split);
void				ft_two_del(char **array);
void				ft_swapch(char **a, char **b);
char				*ft_strjoin_free(char *s1, char *s2, _Bool s1b, _Bool s2b);
int					ft_numlen(int num);
void				ft_tabputs(char *str, _Bool endl);
void				ft_puts_except(const char *str, char ch);
void				ft_puts_except_rev(const char *str, char ch);
int					ft_free_twodm(char **arr);
char				*ft_realloc(char *ptr, size_t size);
size_t				ft_strlench(const char *s, char ch);
char				*ft_strdupch(const char *s1, char ch);
int					ft_occpos(char *str, char occ);
char				**ft_strsplit_many(char const *s, const char *dels);
int					is_user_a_goat(void);
char				*ft_strsjoin(int amount, ...);
int					count_occ(const char *str, char occ);
char				*remove_occ(char *str, char occ);
char				**ft_strsplit_smart(char const *s, const char *dels);
char				*ft_strdup_char(char c);
char				*ft_strjoin_bytes(char const *s1, char const *s2,
					size_t size1, size_t size2);
/*
** LISTS.
*/

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
