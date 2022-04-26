#include <stdio.h>
char **ft_splitsane(char *str);
int main(void)
{
	int i = 0;
	char **dest = ft_splitsane("  haha' 'haha lol ");
	while (dest[i])
		printf("%s\n", dest[i++]);
}
