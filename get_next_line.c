/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/06/02 04:29:17 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd_list	*fd_search(int fd, t_fd_list **l)
{
	t_fd_list *curr;

	curr = *l;
	 while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	if (!curr)
	{
		curr = (t_fd_list*)ft_memalloc(sizeof(t_fd_list));
		curr->fd = fd;
		curr->i = 0;
		curr->content = NULL;
		curr->next = *l;
		*l = curr;
	}
	return (curr);
}

void		*ft_memjoin(void const *s1, void const *s2, size_t n1, size_t n2)
{
	size_t	i;
	size_t	j;
	void	*ns;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
	{
		ns = ft_memalloc((!s1) ? n2 : n1);
		if (ns == NULL)
			return (NULL);
		ns = ft_memcpy(ns, ((!s1) ? (void*)s2 : (void*)s1), ((!s1) ? n2 : n1));
		return ((unsigned char*)ns);
	}
	i = -1;
	j = -1;
	ns = (unsigned char*)ft_memalloc(n1 + n2);
	if (ns == NULL)
		return (NULL);
	while (++i < n1)
		((unsigned char*)ns)[i] = ((const unsigned char*)s1)[i];
	while (++j < n2)
		((unsigned char*)ns)[i++] = ((const unsigned char*)s2)[j];
	return ((unsigned char*)ns);
}

int			make_line(size_t r, char *b, t_fd_list	*curr, char **line)
{
	char *tmp;

	tmp = NULL;
	if (ft_memchr(b, '\n', r))
	{
		if (!(tmp = ft_memalloc(ft_memchr(b, '\n', r) - (void*)b + 1)))
			return (0);
		ft_memccpy(tmp, b, '\n', ft_memchr(b, '\n', r) - (void*)b + 1);
		tmp[ft_memchr(b, '\n', r) - (void*)b] = '\0';
		*line = (char*)ft_memjoin(curr->content, tmp,
			curr->i, ft_memchr(b, '\n', r) - (void*)b + 1);
		ft_memdel((void*)&tmp);
		tmp = curr->content;
		curr->content = (char*)ft_memjoin(ft_memchr(b, '\n', r) + 1, NULL,
			(void*)b + BUFF_SIZE - 1 - ft_memchr(b, '\n', r), 0);
		curr->i = (void*)b + BUFF_SIZE - 1 - ft_memchr(b, '\n', r);
		ft_memdel((void*)&tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	size_t				r;
	char				b[BUFF_SIZE + 1];
	static t_fd_list	*l = NULL;
	t_fd_list			*curr;
	char				*tmp;

	if (fd < 0 || !line)
		return (-1);
	curr = fd_search(fd, &l);
	r = 1;
	tmp = NULL;
	while (0 < (r = read(curr->fd, b, BUFF_SIZE)))
	{
		if (make_line(r, b, curr, line))
			return (1);
		tmp = curr->content;
		curr->content = (char*)ft_memjoin(curr->content, b, curr->i, r + 1);
		curr->i += r;
		ft_memdel((void*)&tmp);
	}
	curr->i = 0;
	*line = curr->content;
	ft_memdel((void*)&(curr->content));
	return (0);
}
