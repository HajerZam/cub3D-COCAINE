/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:58:49 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/12 11:07:27 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_dda(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
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
			|| game->scene.map.grid[ray->map_y][ray->map_x] == 'D')
			hit = 1;
	}
}

static void	render_wall(t_game *game, t_ray *ray, int x)
{
	int	tex_index;

	init_ray(game, x, ray);
	setup_dda(game, ray);
	perform_dda(game, ray);
	calc_wall_dist(ray);
	calc_wall_height(ray);
	tex_index = select_texture(ray, game);
	calc_tex_x(game, ray, tex_index);
	draw_wall_column(game, ray, x, tex_index);
}

static void	render_open_door(t_game *game, t_ray *ray, int x)
{
	init_ray(game, x, ray);
	setup_dda(game, ray);
	perform_dda_door(game, ray);
	if (game->scene.map.grid[ray->map_y][ray->map_x] != 'O')
		return ;
	calc_wall_dist(ray);
	calc_wall_height(ray);
	calc_tex_x(game, ray, DOOR_OPEN);
	open_door(game, ray, x, DOOR_OPEN);
}

void	render_frame(t_game *game)
{
	t_ray	ray;
	t_ray	door_ray;
	int		x;

	x = 0;
	while (x < SCREEN_W)
	{
		render_wall(game, &ray, x);
		render_open_door(game, &door_ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
}
