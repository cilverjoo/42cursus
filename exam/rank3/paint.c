#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct	s_zone
{
	int			width;
	int			height;
	char		background;
}				t_zone;

typedef struct s_shape
{
	char		type;
	float		x;
	float		y;
	float		radius;
	char		color;
}				t_shape;

int			str_error(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (1);
}

int			clear_all(FILE *file, char *drawing)
{
	fclose(file);
	if (drawing)
		free(drawing);
	return (1);
}

char		*get_zone(FILE *file, t_zone *zone)
{
	int		i;
	char	*tmp;

	if (fsacnf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return (NULL);
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->width > 300)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * (zone->width * zone->height))))
		return (NULL);
	i = 0;
	while (i < zone->width * zone->height)
		tmp[i++] = zone->background;
	return (tmp);
}

int			in_circle(float x, float y, t_shape *shape)
{
	float	distance;

	distance = sqrtf(powf(x - shape->x, 2.00000000) + powf(y - shape->y, 2.00000000));
	if (distance <= shape->radius)
	{
		if ((shape->radius - distance) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void		draw_shape(t_zone *zone, char *drawing, t_shape *shape)
{
	int		x;
	int		y;
	int		ret;

	y = 0;
	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			ret = in_circle((float)x, (float)y, shape);
		}
	}
}

int			draw_shapes(FILE *file, t_zone *zone, char *drawing)
{
	t_shape	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
			return (0);
		draw_shape(zone, drawing, &tmp);
	}
	if (ret != -1)
		return (0);
	return (1);
}

int main(int argc, char **av)
{
	FILE	*file;
	char	*drawing;
	t_zone	zone;

	zone.width = 0;
	zone.height = 0;
	zone.background = 0;
	drawing = NULL;
	if (argc != 2)
		return (str_error("Error: argument\n"));
	if (!(file = fopen(av[1], "r")))
		return (str_error("Error: Operation file corrupted\n"));
	if (!(drawing = get_zone(file, &zone)))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n"));
	if (!(draw_shapes(file, &zone, drawing)))
		return (clear_all(file, drawing) && str_error("Error: Operation file corrupted\n"));
	draw_drawing(&zone, drawing);
	clear_all(file, drawing);
	return (0);
}