/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:41:08 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/12 11:07:43 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_tex_x(t_game *game, t_ray *ray, int tex_idx)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)game->textures[tex_idx].width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = game->textures[tex_idx].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = game->textures[tex_idx].width - ray->tex_x - 1;
}

void	init_draw(t_game *game, t_ray *ray, t_draw *d, int tex_idx)
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
			if (d->tex_idx != DOOR_OPEN || (d->color & 0xFFFFFF) != 0)
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
