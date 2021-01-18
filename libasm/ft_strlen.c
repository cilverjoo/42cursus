#include <stdio.h>

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			main(void)
{
	char	*str = "this is competition";
	int		len;

	len = ft_strlen(str);
	printf("%d\n", len);
	return (0);
}
