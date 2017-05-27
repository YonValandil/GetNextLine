#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
  //int r;
  int fd;
  char *line;


  line = NULL;
  if (argc > 1)
  {
    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
      printf("%s\n", line);
    //printf("\nreturn GNL : %d\n", r);
      free(line);
    }
    //get_next_line(fd, argv);
    //get_next_line(fd, argv);
    //printf("\n\nreturn GNL : %d\n", r);
//    if (close                                                                                                                                                                                                            (fd))
//      write(2, "file close failed\n", 18);
  }
	else
		write(2, "arguments missing.\n", 19);
  return (0);
}
