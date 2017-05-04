#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
  int r;
  int fd;

  if (argc > 1)
  {
    fd = open(argv[1], O_RDONLY);
    r	=	get_next_line(fd, argv);
    printf("\n\nreturn GNL : %d\n", r);
    if (close(fd))
      write(2, "file close failed\n", 18);
  }
	else
		write(2, "arguments missing.\n", 19);
  return (0);
}
