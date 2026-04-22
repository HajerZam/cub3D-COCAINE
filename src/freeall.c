#include "cub3d.h"

static void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
		free(grid[i++]);
	free(grid);
}

void	free_scene(t_scene *scene)
{
	free(scene->config.no_path);
	free(scene->config.so_path);
	free(scene->config.we_path);
	free(scene->config.ea_path);
	free_grid(scene->map.grid, scene->map.height);
}
