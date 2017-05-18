/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/18 06:29:32 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_memjoin(void const *s1, void const *s2, size_t n1, size_t n2)
{
	int		i;
	int		j;
	char	*ns;

	if (!s1 && !s2)
		return (0);
	if (!s1)
	{
		ns = ft_memalloc(n1);
		if (ns == NULL)
			return (NULL);
		ns = ft_memcpy((void*)s1, ns, n1);
		return ((unsigned char*)ns);
	}
	if (!s2)
	{
		ns = ft_memalloc(n2);
		if (ns == NULL)
			return (NULL);
		ns = ft_memcpy((void*)s2, ns, n2);
		return ((unsigned char*)ns);
	}
	i = -1;
	j = -1;
	ns = ft_memalloc(n1 + n2);
	if (ns == NULL)
		return (NULL);
	while (((const unsigned char*)s1)[++i] < n1)
		ns[i] = ((const unsigned char*)s1)[i];
	while (((const unsigned char*)s2)[++j] < n2)
		ns[i++] = ((const unsigned char*)s2)[j];
	return ((unsigned char*)ns);
}

int		get_next_line(const int fd, char **line)
{
	int				r;
	char			b[BUFF_SIZE + 1];
	static t_list	*l = NULL;
	//t_list		*curr;
	char			*tmp;
	int				i;

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
			*line = ft_memjoin(l->content, tmp, i, ft_memchr(b, '\n', r) - (void*)b + 1);
			ft_memdel((void*)&(l->content));
			l->content = ft_memjoin(l->content, tmp, 0, ft_memchr(b, '\n', r) - (void*)b + 1);
			ft_memdel((void*)&tmp);
			//ft_memdel((void*)&(l->content));
			//l->content = ft_memcpy(l->content, ft_memchr(buf, '\n', r), r);
			//l->content = ft_memjoin(l->content, ft_memchr(b, '\n', r), r, );
			break ;
		}

		tmp = l->content;
		l->content = ft_memjoin(l->content, b, i, r);
		i += r;
		ft_memdel((void*)&tmp);
	}
	//printf("\n%s\n", (char*)l->content);
	ft_memdel((void*)&(l->content));
	return (1);
}
