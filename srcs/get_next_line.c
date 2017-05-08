/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/08 06:44:58 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	int				r;
	char			b[BUFF_SIZE + 1];
	static t_list	*l = NULL;
	//t_list		*curr;
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);

	if (!l)
		l = ft_lstnew("\0", 1); // "" to null
	//l->content = ft_memalloc(sizeof(char) * 1);

	r = 1;
	tmp = NULL;
	//curr = lst;

	while (0 < (r = read(fd, b, BUFF_SIZE)) && !(ft_memchr(l->content, '\n', r)))
	{
		b[r] = '\0';
		//if (!(ft_memchr(l->content, '\n', r))) //|| !l->content
		//{
			tmp = l->content;
			l->content = ft_strjoin(l->content, b);
			ft_memdel((void*)&tmp);
		//}
	}
	ft_putstr(l->content);
	//printf("\n%s\n", (char*)l->content);
	ft_memdel((void*)&(l->content));
	return (1);
}
