#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef struct 	stat	t_stat;

int	main(int ac, char **av)
{
	t_stat	stat;

	if(ac != 2)
	return (0);

	lstat(av[1], &stat);
	return (0);
}	
