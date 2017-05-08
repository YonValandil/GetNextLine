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
	int				rd;
	char			buf[BUF_SIZE + 1];
	static t_list	*lst = NULL;
	//t_list		*curr;
	char			*tmp;

	if (!lst)
		lst = ft_lstnew("", 0); // "" to null
	//lst->content = ft_memalloc(1);

	rd = 1;
	tmp = NULL;
	//curr = lst;
	if (fd < 0 || !line)
		return (-1);
	while (0 < (rd = read(fd, buf, BUF_SIZE)))
	{
		buf[rd] = '\0';
		if (!(ft_memchr(lst->content, '\n', rd))) //|| !lst->content
		{
			tmp = lst->content;
			lst->content = ft_strjoin(lst->content, buf);
			ft_memdel((void*)&tmp);
		}
	}
	ft_putstr(lst->content);
	ft_memdel((void*)&(lst->content));
	return (1);
}
