#include "cub3d.h"

// Returns 1 if the line is a map line (only valid map chars)
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (i > 0);
}

// Adds one row to map.grid, growing the array
static void	add_map_row(t_scene *scene, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (scene->map.height + 2));
	if (!new_grid)
		error_exit("malloc failed");
	i = 0;
	while (i < scene->map.height)
	{
		new_grid[i] = scene->map.grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(line);
	new_grid[i + 1] = NULL;
	free(scene->map.grid);
	scene->map.grid = new_grid;
	scene->map.height++;
}

void	parse_config(char *file_path, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			if (scene->parser.map_started && !scene->parser.map_ended)
				scene->parser.map_ended = 1;
			continue ;
		}
		if (!scene->parser.map_started && !is_map_line(line))
			parse_identifier(line, scene);
		else
		{
			if (scene->parser.map_ended)
				error_exit("Non-empty line after map ended");
			scene->parser.map_started = 1;
			add_map_row(scene, line);
		}
		free(line);
	}
	close(fd);
	if (scene->map.height == 0)
		error_exit("No map found in file");
	validate_config(scene);
	map_validation(scene);
}
