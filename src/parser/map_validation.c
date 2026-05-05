#include "cub3d.h"

static void	normalize_map(t_scene *scene)
{
	int		i;
	int		len;
	int		max_width;
	char	*padded;

	max_width = 0;
	i = -1;
	while (++i < scene->map.height)
	{
		len = ft_strlen(scene->map.grid[i]);
		if (len > 0 && scene->map.grid[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
	}
	scene->map.width = max_width;
	i = -1;
	while (++i < scene->map.height)
	{
		len = ft_strlen(scene->map.grid[i]);
		if (len > 0 && scene->map.grid[i][len - 1] == '\n')
			len--;
		padded = ft_calloc(max_width + 1, sizeof(char));
		if (!padded)
			error_exit("malloc failed");
		ft_memcpy(padded, scene->map.grid[i], len);
		while (len < max_width)
			padded[len++] = ' ';
		free(scene->map.grid[i]);
		scene->map.grid[i] = padded;
	}
}

static char	**copy_grid(t_scene *scene)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (scene->map.height + 1));
	if (!copy)
		error_exit("malloc failed");
	i = -1;
	while (++i < scene->map.height)
	{
		copy[i] = ft_strdup(scene->map.grid[i]);
		if (!copy[i])
			error_exit("malloc failed");
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **grid, int x, int y, int w, int h)
{
	if (y < 0 || y >= h || x < 0 || x >= w)
		error_exit("Map is not closed (out of bounds)");
	if (grid[y][x] == ' ')
		error_exit("Map is not closed (reachable space)");
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y, w, h);
	flood_fill(grid, x - 1, y, w, h);
	flood_fill(grid, x, y + 1, w, h);
	flood_fill(grid, x, y - 1, w, h);
}

static void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static void	check_flood(t_scene *scene)
{
	char	**copy;

	copy = copy_grid(scene);
	flood_fill(copy, scene->spawn.x, scene->spawn.y, scene->map.width,
		scene->map.height);
	free_grid(copy);
}

static void	add_char(t_scene *scene, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (scene->spawn.found)
			error_exit("Multiple player spawns found");
		scene->spawn.found = 1;
		scene->spawn.x = x;
		scene->spawn.y = y;
		scene->spawn.direction = c;
	}
}

void	map_validation(t_scene *scene)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < scene->map.height)
	{
		j = -1;
		len = ft_strlen(scene->map.grid[i]);
		while (++j < len)
		{
			if (scene->map.grid[i][j] == '\n')
				continue ;
			if (scene->map.grid[i][j] != '1' && scene->map.grid[i][j] != '0'
				&& scene->map.grid[i][j] != 'N' && scene->map.grid[i][j] != 'S'
				&& scene->map.grid[i][j] != 'E' && scene->map.grid[i][j] != 'W'
				&& scene->map.grid[i][j] != 'D')
				error_exit("Invalid character in map");
			add_char(scene, scene->map.grid[i][j], j, i);
		}
	}
	if (!scene->spawn.found)
		error_exit("No player spawn found in map");
	normalize_map(scene);
	check_flood(scene);
}
