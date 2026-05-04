/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:58:49 by halzamma          #+#    #+#             */
/*   Updated: 2026/04/23 10:58:49 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	in it's simplest view_x is a value in [-1, 1]
	-1 = leftmost column, 0 = center, +1 = rightmost column
	the ray direction is: player position + view_x * view plane vector
	the view plane is perpendicular to the direction and its length controls FOV
*/

static void	init_ray(t_game *game, int x, t_ray *ray)
{
	double view_x;

	view_x = 2.0 * x / (double)SCREEN_W - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * view_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * view_x;
	/* Current map cell player is in */
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	/*	delta_distis is how far the ray travels (in world units) to cross 
		one full grid cell, horizontally and vertically
		If dir == 0 the ray is perfectly axis-aligned */
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

/*	DDA setup, aka Digital Differential Analyzer basically a line drawing algorithm used in computer graphics
	to generate a line segment between two specified endpoints*/

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
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
}

/* DDA LOOP */

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
		if (game->scene.map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	calc_tex_x(t_game *game, t_ray *ray, int tex_idx)
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

int	get_texel_color(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel; 

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(int *)pixel);
}

void    render_frame(t_game *game)
{
	t_ray   ray;
	int     tex_index;
	int     x;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(game, x, &ray);
		setup_dda(game, &ray);
		perform_dda(game, &ray);
		calc_wall_dist(&ray);
		calc_wall_height(&ray);
		tex_index = select_texture(&ray);
		calc_tex_x(game, &ray, tex_index);
		draw_wall_column(game, &ray, x, tex_index);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
}