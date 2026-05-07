/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:25:14 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/07 15:50:24 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
}

static void	load_texture(void *mlx_ptr, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		ft_printf("Error\nCannot load texture: %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

static void	mlx_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 6, 1L << 6, mouse_hook, game);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win, 17, 0L, close_hook, game);
}

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit("mlx_init failed");
	game->mlx.win = mlx_new_window(game->mlx.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->mlx.win)
		error_exit("mlx_new_window failed");
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, SCREEN_W, SCREEN_H);
	if (!game->mlx.img.img)
		error_exit("mlx_new_image failed");
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img,
			&game->mlx.img.bpp,
			&game->mlx.img.line_len,
			&game->mlx.img.endian);
	load_texture(game->mlx.mlx, &game->textures[NORTH],
		game->scene.config.no_path);
	load_texture(game->mlx.mlx, &game->textures[SOUTH],
		game->scene.config.so_path);
	load_texture(game->mlx.mlx, &game->textures[WEST],
		game->scene.config.we_path);
	load_texture(game->mlx.mlx, &game->textures[EAST],
		game->scene.config.ea_path);
	load_texture(game->mlx.mlx, &game->textures[DOOR],
		game->scene.config.do_path);
	load_texture(game->mlx.mlx, &game->textures[DOOR_OPEN],
		game->scene.config.dop_path);
	mlx_hooks(game);
}

void	mlx_pixel_put_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
