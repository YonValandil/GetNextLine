/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:37 by jjourne           #+#    #+#             */
/*   Updated: 2017/04/29 03:13:23 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int							rd;
  char						buf[BUF_SIZE + 1];
	static t_list		*lst;
	//t_list					*curr;

	lst = ft_lstnew("", 0);
	//curr = lst;
  if (fd < 0 || !line)
		return (-1);
  while (rd > 0)
  {
    rd = read(fd, buf, BUF_SIZE);
    buf[rd] = '\0';
		ft_strcpy(lst->content, buf);
		//if (lst->content == '\n')
		//{
			ft_putstr(lst->content);
			//rd = 0;
		//}
  }
	//ft_putstr(lst->content);
  return (1);
}
