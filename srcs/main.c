#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
  int r;
  int fd;
  //char *line;

  //if (!(line = (char*)ft_memalloc(sizeof(char*) * (50 + 1))))
	//	return (0);
  if (argc == 2)
  {
    fd = open(argv[1], O_RDONLY);
    //r	=	get_next_line(fd, &line);
    r	=	get_next_line(fd, argv);
    printf("\n\nreturn GNL : %d\n", r);
    if (close(fd))
      write(2, "file close failed\n", 18);
    //ft_memdel(&line);
  }
	else if (argc > 2)
		write(2, "Too many arguments.\n", 20);
	else
		write(2, "File name missing.\n", 19);
  return (0);
}
