/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:40:46 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/07 15:49:56 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_SIZE	8
#define MAP_OFFSET_X	10
#define MAP_OFFSET_Y	10

#define COLOR_WALL		0x444444
#define COLOR_FLOOR		0xAAAAAA
#define COLOR_PLAYER	0xFF0000
#define COLOR_RAY		0xFFFF00

void	put_pixel_safe(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1280 || y < 0 || y >= 720)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_tile(t_img *img, int col, int row, int color)
{
	int	px;
	int	py;
	int	sx;
	int	sy;

	sx = MAP_OFFSET_X + col * TILE_SIZE;
	sy = MAP_OFFSET_Y + row * TILE_SIZE;
	py = 0;
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			put_pixel_safe(img, sx + px, sy + py, color);
			px++;
		}
		py++;
	}
}

static void	draw_map_grid(t_game *game)
{
	int	row;
	int	col;
	int	color;

	row = 0;
	while (row < game->scene.map.height)
	{
		col = 0;
		while (col < game->scene.map.width)
		{
			if (game->scene.map.grid[row][col] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_tile(&game->mlx.img, col, row, color);
			col++;
		}
		row++;
	}
}

static void	draw_player_dot(t_game *game)
{
	int		px;
	int		py;
	int		i;
	int		j;
	double	dir_len;

	px = MAP_OFFSET_X + (int)(game->player.x * TILE_SIZE);
	py = MAP_OFFSET_Y + (int)(game->player.y * TILE_SIZE);
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			put_pixel_safe(&game->mlx.img, px + j, py + i, COLOR_PLAYER);
			j++;
		}
		i++;
	}
	dir_len = 0;
	while (dir_len < TILE_SIZE)
	{
		put_pixel_safe(&game->mlx.img,
			px + (int)(game->player.dir_x * dir_len),
			py + (int)(game->player.dir_y * dir_len), COLOR_RAY);
		dir_len += 0.5;
	}
}

void	draw_minimap(t_game *game)
{
	draw_map_grid(game);
	draw_player_dot(game);
}
