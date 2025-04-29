/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:38:02 by mliyuan           #+#    #+#             */
/*   Updated: 2024/01/09 18:16:15 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>

//part 1
int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *str, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);

void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s);

//part 2
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

//extra add-on
int			ft_perror_fd(char *s, int fd, int value);

// printf function
int			ft_printf(const char *str, ...);

//helper function
int			ft_char_helper(va_list args);
int			ft_str_helper(va_list args);
int			ft_num_helper(va_list args);
int			ft_uint_helper(va_list args);
int			ft_hexa_upper_helper(va_list args);
int			ft_hexa_lower_helper(va_list args);
int			ft_memory_helper(va_list args);
//printf utils function
int			ft_printchar(const char chr);
int			ft_printstr(const char *str);
int			ft_printnum(int num);
int			ft_printuint(unsigned long num);
int			ft_printhexa_upper(unsigned long num);
int			ft_printhexa_lower(unsigned long num);
int			ft_printmemory(uintptr_t ptr);

//gnl function
typedef struct s_gnl_list
{
	char				*content;
	struct s_gnl_list	*next;
}					t_gnl_list;

char		*get_next_line(int fd);
void		get_buffer(int fd, t_gnl_list **lst);
void		add_to_lst(char *buffer, t_gnl_list **lst);
char		*return_line(t_gnl_list *lst);
void		clear_lst(t_gnl_list **lst);
int			ft_newline(t_gnl_list *lst);
int			ft_len_newline(t_gnl_list *lst);
void		\
dealloc(t_gnl_list **linked_list, t_gnl_list **clean_node, char **buffer);
void		append_str(t_gnl_list *lst, char *str);
t_gnl_list	*ft_llstlast(t_gnl_list *lst);

//bonus
typedef struct s_list
{
	void			*content;
	// int				export_id;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));

#endif
