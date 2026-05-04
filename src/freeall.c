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

void	free_game(t_game *game)
{
	int	i;

	/* 1. Scene: texture paths + map grid
	   ROOT: malloc'd by ft_strdup in dup_strip (parse_config.c)
	         and ft_calloc in normalize_map (map_validation.c) */
	free_scene(&game->scene);

	/* 2. Four texture images
	   ROOT: malloc'd internally by mlx_xpm_file_to_image in load_texture
	         (init_graph.c), one per wall direction */
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx.mlx, game->textures[i].img);
		i++;
	}

	/* 3. Frame buffer image
	   ROOT: malloc'd internally by mlx_new_image in init_mlx (init_graph.c)
	         this is the off-screen buffer we render into every frame */
	if (game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);

	/* 4. Window
	   ROOT: malloc'd internally by mlx_new_window in init_mlx (init_graph.c) */
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);

	/* 5. MLX connection itself
	   ROOT: malloc'd internally by mlx_init in init_mlx (init_graph.c)
	         mlx_destroy_display frees X11 internals, then free() frees
	         the mlx struct pointer itself */
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
}
