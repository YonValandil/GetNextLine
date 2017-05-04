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
	int rd;
  char buf[BUF_SIZE + 1];

  if (fd < 0 || !line)
		return (-1);
  while (rd > 0)
  {
    rd = read(fd, buf, BUF_SIZE);
    buf[rd] = '\0';
    ft_putstr(buf);
  }
  return (1);
}
