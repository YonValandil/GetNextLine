/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 04:27:49 by jjourne           #+#    #+#             */
/*   Updated: 2017/06/03 18:44:33 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int		main(int argc, char *argv[])
{
	int		fd;
	// int		fd2;
	char	*line;
	// char	*line2;
	int		ret;

	line = NULL;
	// line2 = NULL;
	ret = 0;

	fd = open(argv[1], O_RDONLY);
	ret = get_next_line(fd, &line);
	printf("*%s*\n", line);
	printf(">>>> %d\n", ret);


	free(line);
	// fd2 = open(argv[argc], O_RDONLY);
	ret = get_next_line(fd, &line);
	printf("*%s*\n", line);
	printf(">>>> %d\n", ret);

	free(line);
	ret = get_next_line(fd, &line);
	printf("*%s*\n", line);
	printf(">>>> %d\n", ret);
/*
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			ft_putendl(line);
			free(line);
			while (get_next_line(fd2, &line2) > 0)
			{
				ft_putendl(line2);
				free(line2);
			}
		}
	}
	else
		write(2, "arguments missing.\n", 19);
*/
	return (0);

}