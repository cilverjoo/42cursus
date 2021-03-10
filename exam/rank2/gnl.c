#include <stdlib.h>
#include <unistd.h>

char    *ft_strjoin(char *str, char c)
{
	int  i = 0;
	int  j = 0;
	char *ret;

	if (!str)
	{
		ret = (char *)malloc(sizeof(char) * 2);
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	else
	{
		while (str[i])
			i++;
		ret = (char *)malloc(sizeof(char) * (i + 2));
		while (j < i)
		{
			ret[j] = str[j];
			j++;
		}
		ret[j++] = c;
		ret[j] = '\0';
		return (ret);
	}
}

int    get_next_line(char **line)
{
	char *tmp = NULL;
	char c;

	if (tmp == NULL)
		tmp = ft_strjoin(tmp, '\0');
	while (read(0, &c, 1) && c != '\n')
	{
		tmp = ft_strjoin(tmp, c);
	}
	*line = tmp;
	return (c=='\n');
}