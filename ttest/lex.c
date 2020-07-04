#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	a[2] = "aa";
	char	b[2] = "bb";
	int	i;

	i = strcmp(a, b);
	printf("%i\n", i);
	return (0);
}
