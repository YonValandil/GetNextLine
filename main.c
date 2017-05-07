#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
    char	*file_content;

    if (argc == 2)
    {
            file_content = read_file(argv[1]);
			ft_memdel((void*)&file_content;
    }
    else
        write(2, "not only 1 argument \n", 21);
	return (0);
}
