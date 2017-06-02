#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
  int fd;
  int fd2;
  char *line;
  char *line2;

  line = NULL;
  line2 = NULL;
  if (argc > 1)
  {
    fd = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
      //printf("%s\n", line);
      free(line);
      while (get_next_line(fd2, &line2) > 0)
      {
        //printf("%s\n", line2);
        free(line2);
      }
    }
  }
	else
		write(2, "arguments missing.\n", 19);
  return (0);
}
