/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/06/03 18:42:16 by jjourne          ###   ########.fr       */
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
		{
			// printf("curr while -> %s\n", curr->content);
			return (curr);
		}
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


/*
	que fait make_line ?
	il modifie curr->content
	c est debile

	current content =string genre "12345678"

	deuxieme read 79101112
	join 12345678 9101112

	male line
	strsub jusqu a \n ou tout
	foutre tout ce qu il y a ou qui reste dans line
	et sub ce qu on a print

	curr content 1324\n56
	malloc ft_strlen \n to 6
	memcpy
	free

*/
int			make_line(size_t r, char *b, t_fd_list *curr, char **line)
{
	char *tmp;

	tmp = NULL;
	if (ft_memchr(b, '\n', r))
	{
		printf("Start Make Line\n");
		if (!(tmp = ft_memalloc(ft_memchr(b, '\n', r) - (void*)b + 1)))
			return (0);
		ft_memccpy(tmp, b, '\n', ft_memchr(b, '\n', r) - (void*)b + 1);
		tmp[ft_memchr(b, '\n', r) - (void*)b] = '\0';
		// printf("tmp -> %s\n", tmp);
		printf("curr -> %s\n", curr->content);
		*line = (char*)ft_memjoin(curr->content, tmp,
			curr->i, ft_memchr(b, '\n', r) - (void*)b + 1);
		printf("line -> %s\n", *line);
		printf("buff %s\n", b);
		ft_memdel((void*)&tmp);
		//ft_memdel((void*)&(curr->content));
		tmp = curr->content;


		curr->content = (char*)ft_memjoin(ft_memchr(b, '\n', r) + 1, NULL,
			(void*)b + BUFF_SIZE - 1 - ft_memchr(b, '\n', r), 0);


		printf("curr pouet -> %s\n", curr->content);
		curr->i = (void*)b + BUFF_SIZE - 1 - ft_memchr(b, '\n', r);
		ft_memdel((void*)&tmp);
		return (1);
	}
	return (0);
}

int		make_line_2(t_fd_list *curr, char **line)
{
	char *tmp;

	tmp = NULL;
	if (ft_memchr(curr->content, '\n', curr->i))
	{
		// int size = ft_memchr(curr->content, '\n', curr->i) - curr->content;

		printf("size == %d\n", (ft_memchr(curr->content, '\n', curr->i) - curr->content));

		if(!(*line = (char*)ft_memalloc(sizeof(char) * (ft_memchr(curr->content, '\n', curr->i) - curr->content))))
			return (-1);

		*line = ft_memcpy(*line, curr->content, (ft_memchr(curr->content, '\n', curr->i) - curr->content));


		tmp = curr->content;
		// printf("calcul bizzare %d\n", curr->i - (ft_memchr(curr->content, '\n', curr->i) - curr->content));
		// printf("cur iii %d\n", (int)curr->i);
		// printf("%ld\n", ((curr->content + curr->i) - ft_memchr(curr->content, '\n', curr->i) + 1));

		printf("PONEY %d\n", ((curr->i - (ft_memchr(tmp, '\n', curr->i) - curr->content) + 1)));

		curr->content = (void*)ft_memalloc(sizeof(char) * ((curr->i - (ft_memchr(curr->content, '\n', curr->i) - curr->content) + 1)));

		printf("cur -> %s\n", tmp);
		printf("calculllllllll ==> %d\n", (ft_memchr(tmp, '\n', curr->i) - (void*)tmp));
		ft_memcpy(curr->content, tmp + (ft_memchr(tmp, '\n', curr->i) + 1 - (void*)tmp),
	/*curr->i - (ft_memchr(curr->content, '\n', curr->i) - (void*)tmp)*/ 1);

		//curr->content = ft_memjoin(ft_memchr(curr->content, '\n', curr->i) + 1, NULL, ft_memchr(curr->content, '\n', curr->i) - (curr->content + curr->i) + 1, 0);
		printf("curr fuck%s\n", curr->content);
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
/*
	if (memchr(\n, current content))
		if(make_line)
			return (1);
*/
	while (0 < (r = read(curr->fd, b, BUFF_SIZE)))
	{
		printf("r = %d\n", r);
		printf("buffer %s\n", b);
		tmp = curr->content;
		curr->content = ft_memjoin(curr->content, b, curr->i, r + 1);
		curr->i += r;
		ft_memdel((void*)&tmp);

		printf("curr %s\n", curr->content);
		if (make_line_2(curr, line))
			return (1);
		// tmp = curr->content;
		// curr->content = (char*)ft_memjoin(curr->content, b, curr->i, r + 1);
		// curr->i += r;
		// ft_memdel((void*)&tmp);
	}
	if (curr->content)
	{
		// printf("end>>> %p\n", curr->content);
		*line = curr->content;
		ft_memdel((void*)&(curr->content));
		return (1);
	}
	return (0);
}
