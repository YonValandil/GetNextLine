/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:10:44 by jjourne           #+#    #+#             */
/*   Updated: 2017/04/29 03:21:45 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "libft.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define BUF_SIZE 32

int		get_next_line(const int fd, char **line);

#endif
