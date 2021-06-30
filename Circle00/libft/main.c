#include <stdio.h>
#include "libft.h"

int main()
{
	int i;
	char **strr;

	strr = ft_split("asdf", 0);
	i = 0;
	while(strr[i])
	{
		printf("-%s-\n", strr[i]);
		i++;
	}
	return 0;
}
