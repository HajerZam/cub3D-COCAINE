/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:36:44 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/13 13:36:44 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_movement(t_game *game, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = game->player.x + dx;
	ny = game->player.y + dy;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

static void	move_forward_backward(t_game *game, double *dx, double *dy)
{
	if (game->keys.w)
	{
		*dx += game->player.dir_x * MOVE_SPEED;
		*dy += game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		*dx -= game->player.dir_x * MOVE_SPEED;
		*dy -= game->player.dir_y * MOVE_SPEED;
	}
}

static void	move_left_right(t_game *game, double *dx, double *dy)
{
	if (game->keys.a)
	{
		*dx -= game->player.plane_x * MOVE_SPEED;
		*dy -= game->player.plane_y * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		*dx += game->player.plane_x * MOVE_SPEED;
		*dy += game->player.plane_y * MOVE_SPEED;
	}
}

void	move_player(t_game *game)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	move_forward_backward(game, &dx, &dy);
	move_left_right(game, &dx, &dy);
	apply_movement(game, dx, dy);
}

void	apply_rotation(t_game *game, double cos_a, double sin_a)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}
