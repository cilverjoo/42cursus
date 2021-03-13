# include "get_next_line.h"

int		ft_strlen(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char		*ft_strjoin(char *str1, char *str2)
{
	int		i = 0;
	int		j = 0;
	int		len1 = 0;
	int		len2 = 0;
	char	*res;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	while (i < len1)
	{
		res[i] = str1[i];
		i++;
	}
	while (j < len2)
	{
		res[i + j] = str2[j];
		j++;
	}
	res[i + j] = '\0';
	free(str1);
	return (res);
}

char		*ft_strdup(char *str)
{
	int		idx = 0;
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	while (idx < len)
	{
		res[idx] = str[idx];
		idx++;
	}
	res[idx] = '\0';
	return (res);
}

int			return_new_line_idx(char *str, char c)
{
	int		start = 0;
	int		len = 0;

	len = ft_strlen(str);
	start = (len - 128 > 0 ? len - 128 : 0);
	while (start < len)
	{
		if (str[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

char   *ft_strduprange(char *str, int start, int end)
{
	int idx = 0;
	char *res;

	if (start > end)
	{
		res = ft_strdup("");
		return (res);
	}
	res = (char *)malloc(sizeof(char) * (end - start + 2));
	while (start <= end)
		res[idx++] = str[start++];
	res[idx] = '\0';
	return (res);
}


int    get_next_line(char **line)
{
	static char *st;
	char 		buffer[129];
	char		*temp_st;
	int			readed = 0;
	int			n_idx = -1;
	
	buffer[128] = '\0';
	if (line == 0)
		return (-1);
	if (st)
	{
		if ((n_idx = return_new_line_idx(st, '\n')) >= 0)
		{
			*line = ft_strduprange(st, 0, n_idx - 1);
			temp_st = st;
			st = ft_strduprange(st, n_idx + 1, ft_strlen(st) - 1);
			free(temp_st);
			return (1);
		}
	}
	while ((readed = read(0, buffer, 128)) > 0)
	{
		buffer[readed] = '\0';
		st = ft_strjoin(st, buffer);
		if ((n_idx = return_new_line_idx(st, '\n')) >= 0)
		{
			*line = ft_strduprange(st, 0, n_idx - 1);
			temp_st = st;
			st = ft_strduprange(st, n_idx + 1, ft_strlen(st) - 1);
			free(temp_st);
			return (1);
		}
	}
	if (st)
	{
		*line = ft_strdup(st);
		free(st);
		st = 0;
	}
	else
		*line = ft_strdup("");
	return (0);
}