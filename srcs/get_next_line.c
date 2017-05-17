/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/09 05:17:09 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_memjoin(void const *s1, void const *s2, size_t n1, size_t n2)
{
	int		i;
	int		j;
	char	*ns;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	ns = ft_memalloc(n1 + n2);
	if (ns == NULL)
		return (NULL);
	while (*(const unsigned char*)s1 < n1)
	{
		ns[i] = ((const unsigned char*)s1)[i];
		++i;
	}
	while (*(const unsigned char*)s2 < n2)
	{
		ns[i] = ((const unsigned char*)s2)[j];
		++j;
		++i;
	}
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
	//	l = ft_lstnew("", 1); // "" to null
		l = ft_lstnew(NULL, 0); // "" to null

	//l = ft_memalloc(sizeof(t_list));
	//l->content = ft_memalloc(1);
	//l->content = NULL;
	//l->content_size = 0;

	r = 1;
	i = 0;
	tmp = NULL;
	//curr = lst;

	while (0 < (r = read(fd, b, BUFF_SIZE)) /*&& !(ft_memchr(l->content, '\n', r))*/)
	{
		b[r] = '\0';
		printf("ligne lu : %s\n", b);
		if (!(ft_memchr(b, '\n', r))) //|| !l->content
		{
			tmp = l->content;
			//l->content = ft_strjoin(l->content, b);
			l->content = ft_memjoin(l->content, b, i, r);
			i += r;
			ft_memdel((void*)&tmp);
		}
		else
		{
			//*line = ft_memjoin(l->content, b, i, r);
			break ;
		}
	}
	//ft_putstr(l->content);
	printf("\n%s\n", (char*)l->content);
	ft_memdel((void*)&(l->content));
	return (1);
}
