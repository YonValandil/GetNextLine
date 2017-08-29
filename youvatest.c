#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	ft_putstr("TEST unitaire YOUVA\n\n");
	while (get_next_line(fd, &line) > 0)
	{
		ft_putchar('*');
		ft_putstr(line);
		ft_putstr("*");
		ft_strdel(&line);
		ft_putstr("\n");
	}
	return (0);
}
