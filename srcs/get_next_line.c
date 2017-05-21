/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/18 06:37:36 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		ns = ft_memcpy(ns, ((!s1) ? (void*)s2 : (void*)s1) , ((!s1) ? n2 : n1));
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
	size_t				i;
	char			b[BUFF_SIZE + 1];
	static t_list	*l = NULL;
	//t_list		*curr;
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);

	if (!l)
		l = ft_lstnew(NULL, 0);

	r = 1;
	i = 0;
	tmp = NULL;
	//curr = lst;

	while (0 < (r = read(fd, b, BUFF_SIZE)))
	{
		b[r] = '\0';
		if (ft_memchr(b, '\n', r))
		{
			if (!(tmp = ft_memalloc(ft_memchr(b, '\n', r) - (void*)b + 1)))
				return (0);
			ft_memccpy(tmp, b, '\n', ft_memchr(b, '\n', r) - (void*)b + 1);
			//tmp[ft_memchr(b, '\n', r) - (void*)b + 1] = '\0';
			printf("\navant line:\ncontent = %s\ntmp = %s\njoin = %s\n", (char*)l->content, tmp, (char*)(ft_memjoin(l->content, tmp, i, ft_memchr(b, '\n', r) - (void*)b + 1)));
			//*line = ft_memjoin(l->content, tmp, i, ft_memchr(b, '\n', r) - (void*)b + 1);
			*line = ft_strjoin(l->content, tmp);
			//ft_memdel((void*)&(l->content));
			l->content = ft_memjoin(tmp, NULL, ft_memchr(b, '\n', r) - (void*)b + 1, 0);
			i = ft_memchr(b, '\n', r) - (void*)b + 1;
			//ft_memdel((void*)&tmp);
			printf("\nline in GNL = %s\n", *line);
			return (1);
		}
		tmp = l->content;
		l->content = (char*)ft_memjoin(l->content, b, i, r + 1);
		i += r;
		ft_memdel((void*)&tmp);
	}
	((char*)l->content)[i] = '\0';
	//ft_putstr((char*)l->content);

	//*line = ft_memjoin(l->content, tmp, i, ft_memchr(b, '\n', r) - (void*)b + 1);
	//ft_memdel((void*)&(l->content));
	//ft_memdel((void*)&l);
	return (1);
}
