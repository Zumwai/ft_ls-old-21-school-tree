#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int	main(int ac, char **av)
{
	DIR  *fold;
	int	i;
	struct dirent *red;
	struct stat *info;

	if (ac < 2)
		return (0);
	i = 1;
	while(i < ac)
	{
		fold = opendir(av[i]);
		printf("ERROR %s - %s\n", av[i], strerror(errno));
		while((red=readdir(fold)) != NULL)
			printf("%u %s\n", red->d_type, red->d_name);
		free(fold);
		i++;
	}
	return (0);
}	
