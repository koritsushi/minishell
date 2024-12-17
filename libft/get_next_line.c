/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:01 by mliyuan           #+#    #+#             */
/*   Updated: 2024/12/06 14:47:26 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_gnl_list		*lst;
	char					*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	get_buffer(fd, &lst);
	if (lst == NULL)
		return (NULL);
	buffer = return_line(lst);
	clear_lst(&lst);
	return (buffer);
}

void	get_buffer(int fd, t_gnl_list **lst)
{
	int		readed_characters;
	char	*buffer;

	while (ft_newline(*lst) != 1)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		readed_characters = read(fd, buffer, BUFFER_SIZE);
		if (readed_characters == 0)
		{
			free(buffer);
			return ;
		}
		buffer[readed_characters] = '\0';
		add_to_lst(buffer, lst);
	}
}

void	add_to_lst(char *buffer, t_gnl_list **lst)
{
	t_gnl_list	*new_node;
	t_gnl_list	*last_node;

	last_node = ft_llstlast(*lst);
	new_node = malloc(sizeof(t_gnl_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

char	*return_line(t_gnl_list *lst)
{
	int		len;
	char	*str;

	if (lst == NULL)
		return (NULL);
	len = ft_len_newline(lst);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	append_str(lst, str);
	return (str);
}

void	clear_lst(t_gnl_list **lst)
{
	t_gnl_list	*last_node;
	t_gnl_list	*clean_node;
	char		*buffer;
	int			i;
	int			j;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_node = malloc(sizeof(t_gnl_list));
	if (clean_node == NULL || buffer == NULL)
		return ;
	last_node = ft_llstlast(*lst);
	while (last_node->content[i] != '\0' && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] != '\0')
		buffer[j++] = last_node->content[++i];
	buffer[j] = '\0';
	clean_node->content = buffer;
	clean_node->next = NULL;
	dealloc(lst, &clean_node, &buffer);
}
