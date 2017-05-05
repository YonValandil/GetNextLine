/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/05/05 23:01:40 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int				rd;
	char			buf[BUF_SIZE + 1];
	static t_list	*lst;
	//t_list		*curr;
	char			*tmp;

	lst = ft_lstnew("", 0);
	rd = 1;
	tmp = NULL;
	//curr = lst;
	if (fd < 0 || !line)
		return (-1);
	while (rd > 0)
	{
		rd = read(fd, buf, BUF_SIZE);

		//lst->content = (char*)ft_memalloc(sizeof(char) * ft_strlen(buf));
		tmp = (char*)ft_memalloc(sizeof(char) * ft_strlen(buf));
		//tmp = buf;
		tmp = lst->content;
		lst->content = ft_strjoin(lst->content, buf);
		ft_memdel((void*)&tmp);

		//tmp = ft_strjoin(lst->content, buf);
		//ft_memdel((void*)&s);

		buf[rd] = '\0';
	}
	ft_putstr(lst->content);
	return (1);
}
