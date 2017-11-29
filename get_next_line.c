/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/11/01 22:06:46 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd_list	*fd_search(int fd, t_fd_list **curr);
static int			make_line(t_fd_list *curr, char **line);
static int			last_check(t_fd_list *curr, char **line);

static t_fd_list	*fd_search(int fd, t_fd_list **l)
{
	t_fd_list	*curr;

	curr = *l;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	if (!curr && (curr = (t_fd_list*)ft_memalloc(sizeof(t_fd_list))))
	{
		curr->fd = fd;
		curr->i = 0;
		curr->content = NULL;
		curr->next = *l;
		*l = curr;
	}
	return (curr);
}

static int			make_line(t_fd_list *curr, char **line)
{
	char *tmp;

	tmp = NULL;
	if (ft_memchr(curr->content, '\n', curr->i))
	{
		if (!(*line = (char*)ft_memalloc(sizeof(char) * (ft_memchr(
			curr->content, '\n', curr->i) - curr->content) + 1)))
			return (-1);
		*line = ft_memcpy(*line, curr->content, (ft_memchr(curr->content, '\n',
						curr->i) - curr->content));
		tmp = curr->content;
		curr->content = ft_memjoin(ft_memchr(curr->content, '\n', curr->i) + 1,
				NULL, (curr->i - (ft_memchr(curr->content, '\n', curr->i) -
						curr->content) + 1), 0);
		curr->i -= (ft_memchr(tmp, '\n', curr->i) - (void *)tmp) + 1;
		ft_memdel((void*)&tmp);
		return (1);
	}
	return (0);
}

static int			last_check(t_fd_list *curr, char **line)
{
	if (curr->i > 0)
	{
		if (make_line(curr, line))
			return (1);
		if (curr->i > 0)
			*line = ft_memcpy(ft_memalloc(curr->i + 1), curr->content, curr->i);
		curr->i = 0;
		ft_memdel((void*)&(curr->content));
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	ssize_t				r;
	char				b[(BUFF_SIZE + 1 < 0) ? 1 : BUFF_SIZE + 1];
	static t_fd_list	*l = NULL;
	t_fd_list			*curr;
	char				*tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!(curr = fd_search(fd, &l)))
		return (-1);
	while (0 < (r = read(curr->fd, b, BUFF_SIZE)))
	{
		tmp = curr->content;
		curr->content = ft_memjoin(curr->content, b, curr->i, r + 1);
		curr->i += r;
		ft_memdel((void*)&tmp);
		if (make_line(curr, line))
			return (1);
	}
	if (r == -1)
		return (-1);
	return (last_check(curr, line));
}
