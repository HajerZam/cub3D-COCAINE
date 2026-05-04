/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:01:24 by halzamma          #+#    #+#             */
/*   Updated: 2026/04/27 14:01:24 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOVE_SPEED	0.05
#define ROT_SPEED	0.03

void	init_player(t_game *game)
{
	t_spawn	*s;

	s = &game->scene.spawn;
	game->player.x = s->x + 0.5;
	game->player.y = s->y + 0.5;
	if (s->direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (s->direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (s->direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static int	is_wall(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= game->scene.map.height)
		return (1);
	if (mx < 0 || mx >= game->scene.map.width)
		return (1);
	return (game->scene.map.grid[my][mx] == '1');
}

static void	move_player(t_game *game)
{
	double	nx;
	double	ny;
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	if (game->keys.w)
	{
		dx += game->player.dir_x * MOVE_SPEED;
		dy += game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		dx -= game->player.dir_x * MOVE_SPEED;
		dy -= game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.a)
	{
		dx -= game->player.plane_x * MOVE_SPEED;
		dy -= game->player.plane_y * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		dx += game->player.plane_x * MOVE_SPEED;
		dy += game->player.plane_y * MOVE_SPEED;
	}
	nx = game->player.x + dx;
	ny = game->player.y + dy;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

static void	rotate_player(t_game *game)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	angle = 0;
	if (game->keys.right)
		angle -= ROT_SPEED;
	if (game->keys.left)
		angle += ROT_SPEED;
	if (angle == 0)
		return ;
	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

/* Called every frame from game_loop */
void	update_player(t_game *game)
{
	move_player(game);
	rotate_player(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	close_hook(t_game *game)
{
	free_game(game);
	exit(0);
}
