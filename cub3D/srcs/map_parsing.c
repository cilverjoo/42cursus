/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:28:56 by ekim              #+#    #+#             */
/*   Updated: 2021/01/14 00:30:16 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			set_screen_size(char *line, t_cub *cub)
{
	int			width;
	int			height;
	int			idx;

	idx = 0;
	width = ft_atoi(line, &idx);
	if (width > 2560)
		cub->res_width = 2560;
	else
		cub->res_width = width;
	height = ft_atoi(&line[idx], &idx);
	if (height > 1440)
		cub->res_height = 1440;
	else
		cub->res_height = height;
	if (height <= 0 || width <= 0)
		exit_program("Screen size error");
}

static char		**read_map_file_to_array(char *path)
{
	int			fd;
	char		*line;
	char		*one_line;
	char		**stack;
	char		*tmp;

	fd = open(path, O_RDONLY);
	one_line = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		if (ft_isalnum(*line) || *line == ' ')
		{
			tmp = ft_free_strjoin(one_line, line);
			one_line = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
			free(line);
	}
	tmp = ft_free_strjoin(one_line, line);
	stack = ft_split(tmp, '\n');
	free(tmp);
	close(fd);
	return (stack);
}

static void		set_cub_textures_path(char **tmp, t_cub *cub)
{
	if (ft_strcmp(tmp[0], "NO") == 0)
		cub->no_path = ft_strdup(tmp[1]);
	else if (ft_strcmp(tmp[0], "SO") == 0)
		cub->so_path = ft_strdup(tmp[1]);
	else if (ft_strcmp(tmp[0], "EA") == 0)
		cub->ea_path = ft_strdup(tmp[1]);
	else if (ft_strcmp(tmp[0], "WE") == 0)
		cub->we_path = ft_strdup(tmp[1]);
	else if (ft_strcmp(tmp[0], "S") == 0)
		cub->sprite_path = ft_strdup(tmp[1]);
	else
		exit_program("Direction in map file is not correct");
}

static void		set_cub_backgrounds(char *cub_line, t_cub *cub)
{
	int			i;

	i = 1;
	if (!check_color_valid(cub_line))
		exit_program("Color value is invalid");
	if (ft_strncmp(cub_line, "F", 1) == 0)
	{
		while (cub_line[i])
			cub->floor_color = cub->floor_color * 256 +
				ft_atoi(&cub_line[i], &i);
	}
	else if (ft_strncmp(cub_line, "C", 1) == 0)
	{
		while (cub_line[i])
			cub->ceiling_color = cub->ceiling_color * 256 +
				ft_atoi(&cub_line[i], &i);
	}
}

void			set_cub(t_window *window, char *path)
{
	char		**cub_file;
	int			i;
	char		**tmp;

	cub_file = read_map_file_to_array(path);
	i = -1;
	while (++i < 8)
	{
		tmp = ft_split(cub_file[i], ' ');
		if (*tmp[0] == 'R')
			set_screen_size(&cub_file[i][1], window->cub);
		else if (ft_strlen(tmp[0]) == 2 || *tmp[0] == 'S')
			set_cub_textures_path(tmp, window->cub);
		else if (*tmp[0] == 'F' || *tmp[0] == 'C')
			set_cub_backgrounds(cub_file[i], window->cub);
		else
			exit_program("Argument in map file is not correct");
		free_array(tmp);
	}
	set_cub_worldmap(cub_file, window);
	free_array(cub_file);
}
