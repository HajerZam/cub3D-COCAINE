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

/* okay so we Set the player's starting position and direction from the parsed spawn.
	direction vectors:
		N → dir=(0,-1)  plane=( 0.66, 0)
		S → dir=(0,+1)  plane=(-0.66, 0)
		E → dir=(+1, 0) plane=(0,  0.66)
		W → dir=(-1, 0) plane=(0, -0.66)
	The camera plane length (0.66) gives ~66° FOV.
	Increase it for a wider FOV, decrease for narrower.
*/
void	init_player(t_game *game)
{
	t_spawn	*s;

	s = &game->scene.spawn;
	game->player.x = s->x + 0.5;
	game->player.y = s->y + 0.5;

	if (s->direction == 'N')
	{
		game->player.dir_x = 0;   game->player.dir_y = -1;
		game->player.plane_x = 0.66; game->player.plane_y = 0;
	}
	else if (s->direction == 'S')
	{
		game->player.dir_x = 0;   game->player.dir_y = 1;
		game->player.plane_x = -0.66; game->player.plane_y = 0;
	}
	else if (s->direction == 'E')
	{
		game->player.dir_x = 1;   game->player.dir_y = 0;
		game->player.plane_x = 0;   game->player.plane_y = 0.66;
	}
	else /* W */
	{
		game->player.dir_x = -1;  game->player.dir_y = 0;
		game->player.plane_x = 0;   game->player.plane_y = -0.66;
	}
}

/*Returns 1 if the map cell at (x, y) is a wall, 0 otherwise.
Guards against out-of-bounds access.*/

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

/*WASD movement
	check for wall collision before committing the move
	small margin (MOVE_SPEED) is here so the player doesn't clip directly into a wall face
*/
static void	move_forward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_x * MOVE_SPEED;
	ny = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

static void	move_backward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_x * MOVE_SPEED;
	ny = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

static void	move_left(t_game *game)
{
	/*move perpendicular to direction (90° left) */
	double	nx;
	double	ny;

	nx = game->player.x - game->player.plane_x * MOVE_SPEED;
	ny = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

static void	move_right(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.plane_x * MOVE_SPEED;
	ny = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (!is_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!is_wall(game, game->player.x, ny))
		game->player.y = ny;
}

/*applying a 2D rotation matrix to (dir_x, dir_y) and (plane_x, plane_y).
	[cos -sin] [dir_x]   [new_dir_x]
	[sin  cos] [dir_y] = [new_dir_y]
	The camera plane must rotate by the same angle to keep FOV constant.
*/
static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(ROT_SPEED);
	sin_a = sin(ROT_SPEED);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(-ROT_SPEED);
	sin_a = sin(-ROT_SPEED);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

/*Called by mlx on every key press, routes keys to the correct action then returns 0 as required by mlx*/
int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_scene(&game->scene);
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		exit(0);
	}
	if (keycode == KEY_W)
		move_forward(game);
	if (keycode == KEY_S)
		move_backward(game);
	if (keycode == KEY_A)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
	if (keycode == KEY_LEFT)
		rotate_left(game);
	if (keycode == KEY_RIGHT)
		rotate_right(game);
	render_frame(game);
	return (0);
}

/*Called when the user clicks the red X on the window*/
int	close_hook(t_game *game)
{
	free_scene(&game->scene);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	exit(0);
}