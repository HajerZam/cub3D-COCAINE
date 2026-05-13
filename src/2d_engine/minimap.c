/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:40:46 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/13 13:12:45 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	draw_dir_ray(t_game *game, int px, int py)
{
	double	dir_len;

	dir_len = 0;
	while (dir_len < TILE_SIZE)
	{
		put_pixel_safe(&game->mlx.img,
			px + (int)(game->player.dir_x * dir_len),
			py + (int)(game->player.dir_y * dir_len), COLOR_RAY);
		dir_len += 0.5;
	}
}

static void	draw_player_dot(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	j;

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
	draw_dir_ray(game, px, py);
}

void	draw_minimap(t_game *game)
{
	draw_map_grid(game);
	draw_player_dot(game);
}
