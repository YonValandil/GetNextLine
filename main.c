#include "get_next_line.h"
#include <stdio.h>

char	*read_file(char *file)
{
	int rd;
	int fd;
	char buf[BUF_SIZE + 1];
	//char *buf;

	rd = 1;
	//buf = ft_memalloc(sizeof(char) * (BUF_SIZE + 1));
	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		while (rd > 0)
		{
			rd = read(fd, buf, BUF_SIZE);
			buf[rd] = '\0';
			return (buf);
		}
		//return (buf); //marche pas pour toutes les taille de buf
	}
	else
		write(2, "Open fd failed\n", 15);
	if (close(fd))
		write(2, "file close failed\n", 18);
	return (0);
}

int		main(int argc, char *argv[])
{
    char	*file_content;

    if (argc == 2)
    {
            file_content = read_file(argv[1]);
    }
    else
        write(2, "not only 1 argument \n", 21);
	return (0);
}
