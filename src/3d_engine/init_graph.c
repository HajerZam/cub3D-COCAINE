/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:25:14 by halzamma          #+#    #+#             */
/*   Updated: 2026/04/23 17:25:14 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCREEN_W	1280
#define SCREEN_H	720

/*short cut to zero out alllll fields of the struct scene lol*/

void	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
}

/*loading tex file to t_img using mlx_xpm_file_to_image and exits with error if file can't load*/

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

/* we start off with creating the mlx connection then we opens a window.
after that make the off-screen image buffer we will render into Loads the four wall textures (NORTH, SOUTH, WEST, EAST).
lastly Hooking keyboard and window-close 
*/

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit("mlx_init failed");
 
	game->mlx.win = mlx_new_window(game->mlx.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->mlx.win)
		error_exit("mlx_new_window failed");
 
	/* Off-screen render target */
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, SCREEN_W, SCREEN_H);
	if (!game->mlx.img.img)
		error_exit("mlx_new_image failed");
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img,
			&game->mlx.img.bpp,
			&game->mlx.img.line_len,
			&game->mlx.img.endian);
 
	/* Textures: order must match enum e_cardinal */
	load_texture(game->mlx.mlx, &game->textures[NORTH],
		game->scene.config.no_path);
	load_texture(game->mlx.mlx, &game->textures[SOUTH],
		game->scene.config.so_path);
	load_texture(game->mlx.mlx, &game->textures[WEST],
		game->scene.config.we_path);
	load_texture(game->mlx.mlx, &game->textures[EAST],
		game->scene.config.ea_path);
 
	/* Event hooks */
	mlx_key_hook(game->mlx.win, key_hook, game);
    mlx_hook(game->mlx.win, 6, 0, mouse_hook, game);
	mlx_hook(game->mlx.win, 17, 0, close_hook, game);  /* window close */
}

/*Helper to write a color into the image buffer at (x, y)*/

void	mlx_pixel_put_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;
 
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
