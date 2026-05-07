/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:41:08 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/07 15:52:24 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_draw(t_game *game, t_ray *ray, t_draw *d, int tex_idx)
{
	d->tex_idx = tex_idx;
	d->ceiling_color = (game->scene.config.ceiling.r << 16)
		| (game->scene.config.ceiling.g << 8)
		| game->scene.config.ceiling.b;
	d->floor_color = (game->scene.config.floor.r << 16)
		| (game->scene.config.floor.g << 8)
		| game->scene.config.floor.b;
	d->tex_step = (double)game->textures[tex_idx].height
		/ (double)ray->line_height;
	d->tex_pos = (ray->draw_start - SCREEN_H / 2
			+ ray->line_height / 2) * d->tex_step;
}

static void	render_column(t_game *game, t_ray *ray, int x, t_draw *d)
{
	int	y;

	y = 0;
	while (y < SCREEN_H)
	{
		if (y < ray->draw_start)
			mlx_pixel_put_to_image(&game->mlx.img, x, y, d->ceiling_color);
		else if (y <= ray->draw_end)
		{
			d->tex_y = (int)d->tex_pos
				& (game->textures[d->tex_idx].height - 1);
			d->tex_pos += d->tex_step;
			d->color = get_texel_color(&game->textures[d->tex_idx],
					ray->tex_x, d->tex_y);
			if (ray->side == 1)
				d->color = (d->color >> 1) & 0x7F7F7F;
			mlx_pixel_put_to_image(&game->mlx.img, x, y, d->color);
		}
		else
			mlx_pixel_put_to_image(&game->mlx.img, x, y, d->floor_color);
		y++;
	}
}

void	draw_wall_column(t_game *game, t_ray *ray, int x, int tex_idx)
{
	t_draw	d;

	init_draw(game, ray, &d, tex_idx);
	render_column(game, ray, x, &d);
}

void	calc_wall_height(t_ray *ray)
{
	ray->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->draw_start = SCREEN_H / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = SCREEN_H / 2 + ray->line_height / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
}

int	select_texture(t_ray *ray, t_game *game)
{
	if (game->scene.map.grid[ray->map_y][ray->map_x] == 'D')
		return (DOOR);
	if (game->scene.map.grid[ray->map_y][ray->map_x] == 'O')
		return (DOOR_OPEN);
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (WEST);
		return (EAST);
	}
	if (ray->step_y > 0)
		return (NORTH);
	return (SOUTH);
}
