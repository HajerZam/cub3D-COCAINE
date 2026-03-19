#include "cub3d.h"

void	line_count(char *file_path, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open the map file");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		scene->parser.row++;
	}
	close(fd);
	free(line);
}

void	parse_config(char *file_path, t_scene *scene)
{
	int	fd;
	int	i;

    i = 0;
	line_count(file_path, scene);
	if (scene->parser.row == 0)
		error_exit("The map file is empty");
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open the map file");
    scene->map.grid = malloc(sizeof(char *) * (scene->parser.row + 1));
    if (!scene->map.grid)
        error_exit("Failed to allocate memory for the map grid");
    while (i < scene->parser.row)
    {
        scene->map.grid[i] = get_next_line(fd);
        if (!scene->map.grid[i])
            error_exit("Failed to read a line from the map file");
        i++;
    }
    scene->map.grid[i] = NULL;
    scene->parser.col = ft_strlen((scene->map.grid[0]) - 1);
    close(fd);
}
