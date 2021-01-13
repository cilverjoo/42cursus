#include "../includes/cub3d.h"

void			set_screen_size(char *line, t_cub *cub)
{
	int		width;
	int		height;
	int		idx;

	idx = 0;
	width = ft_atoi(line, &idx);
	if (width > 2560)
		cub->res_width = 2560;
	else
		cub->res_width = width;
	height = ft_atoi(line, &idx);
	if (height > 1440)
		cub->res_height = 1440;
	else
		cub->res_height = height;
	if (height <= 0 || width <= 0)
		exit_program("Screen size error");
}

void		check_cub_file(char **lines)
{
	int			i;
	int			j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (ft_isascii(lines[i][j]) == 0)
				lines[i][j] = '\0';
			j++;
		}
		i++;
	}
}