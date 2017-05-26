/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/22 22:49:28 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*t_list		*fd_search(int fd, t_list **l)
{
	t_list *current;

	current = l;
	while (current)
	{
		if(current->fd == fd)
			return (curr);
		current = current->next;
	}
	if(!(current = ft_lstnew(NULL, 0)))
		return (NULL);
	current->fd = fd;
	//add a la chaine, ou pas?
	return (current);
}*/

void	*ft_memjoin(void const *s1, void const *s2, size_t n1, size_t n2)
{
	size_t		i;
	size_t		j;
	void			*ns;

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

int		get_next_line(const int fd, char **line)
{
	size_t				r;
	static size_t	i = 0;
	char					b[BUFF_SIZE + 1];
	static 				t_list	*l = NULL;
	//t_list			*curr;
	char					*tmp;
	char					*tmpbuf;

	if (fd < 0 || !line)
		return (-1);
	if (!l)
		l = ft_lstnew(NULL, 0);
	//curr = fd_search(fd, l); //envoyer l'adr du pointeur|remplacer l par curr apres
	r = 1;
	tmp = NULL;
	tmpbuf = NULL;
	while (0 < (r = read(fd, b, BUFF_SIZE)))
	{
		b[r] = '\0';
		if (ft_memchr(b, '\n', r))
		{
			if (!(tmpbuf = ft_memalloc(ft_memchr(b, '\n', r) - (void*)b + 1)))
				return (0);
			ft_memccpy(tmpbuf, b, '\n', ft_memchr(b, '\n', r) - (void*)b + 1);
			tmpbuf[ft_memchr(b, '\n', r) - (void*)b] = '\0';
			*line = ft_memjoin(l->content, tmpbuf, i, ft_memchr(b, '\n', r) - (void*)b + 1);
			tmp = l->content;
			l->content = (char*)ft_memjoin(
				ft_memchr(b, '\n', r) + 1, NULL, (void*)b + 3 - ft_memchr(b, '\n', r), 0);
			i = (void*)b + 3 - ft_memchr(b, '\n', r);
			ft_memdel((void*)&tmp);
			ft_memdel((void*)&tmpbuf);
			printf("%s\n", *line);
			return (1);
		}
		tmp = l->content;
		l->content = (char*)ft_memjoin(l->content, b, i, r + 1);
		i += r;
		ft_memdel((void*)&tmp);
	}
	i = 0;
	*line = l->content;
	printf("%s_", *line);
	ft_memdel((void*)&(l->content)); // supprimer le maillon entier et pas que content ?
	return (1);
}
