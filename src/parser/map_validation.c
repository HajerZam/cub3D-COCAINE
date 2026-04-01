#include "cub3d.h"

void	check_borders(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->parser.row)
	{
		j = 0;
		while (j < scene->parser.col)
		{
			if (i == 0 || i == (scene->parser.row - 1))
				if (scene->map.grid[i][j] != '1')
					error_exit("The map wasn't closed properly");
			if (j == 0 || j == (scene->parser.col - 1))
				if (scene->map.grid[i][j] != '1')
					error_exit("The map wasn't closed properly");
			j++;
		}
		i++;
	}
}

void	add_char(t_scene *scene, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (scene->spawn.found)
			error_exit("Multiple player spawns found in the map file");
		scene->spawn.found = 1;
		scene->spawn.x = scene->parser.col;
		scene->spawn.y = scene->parser.row;
		scene->spawn.direction = c;
	}
}

void	map_validation(t_scene *scene)
{
	int	i;
	int	j;

	i = -1;
	while (++i < scene->parser.row)
	{
		j = -1;
		while (++j < scene->parser.col)
		{
			if (scene->map.grid[i][j] != '1' && scene->map.grid[i][j] != '0'
				&& scene->map.grid[i][j] != 'N' && scene->map.grid[i][j] != 'S'
				&& scene->map.grid[i][j] != 'E' && scene->map.grid[i][j] != 'W'
				&& scene->map.grid[i][j] != '\n')
				error_exit("Invalid character in the map file");
			else
				add_char(scene, scene->map.grid[i][j]);
		}
	}
	check_borders(scene);
	if (!scene->spawn.found)
	{
		free(scene->map.grid);
        error_exit("No player spawn found in the map file");
	}
}
