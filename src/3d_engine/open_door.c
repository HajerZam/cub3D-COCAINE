/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:17:23 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/12 10:17:23 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda_door(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->scene.map.grid[ray->map_y][ray->map_x] == '1'
			|| game->scene.map.grid[ray->map_y][ray->map_x] == 'D'
			|| game->scene.map.grid[ray->map_y][ray->map_x] == 'O')
			hit = 1;
	}
}

void	open_door(t_game *game, t_ray *ray, int x, int tex_idx)
{
	t_draw	d;
	int		y;

	init_draw(game, ray, &d, tex_idx);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		d.tex_y = (int)d.tex_pos & (game->textures[tex_idx].height - 1);
		d.tex_pos += d.tex_step;
		d.color = get_texel_color(&game->textures[tex_idx],
				ray->tex_x, d.tex_y);
		if (ray->side == 1)
			d.color = (d.color >> 1) & 0x7F7F7F;
		if ((d.color & 0xFFFFFF) != 0)
			mlx_pixel_put_to_image(&game->mlx.img, x, y, d.color);
		y++;
	}
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
