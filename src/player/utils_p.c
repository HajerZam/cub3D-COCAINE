/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:46:16 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/13 14:46:16 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Called every frame from game_loop */
void	update_player(t_game *game)
{
	move_player(game);
	rotate_player(game);
}

void	rotate_player(t_game *game)
{
	double	angle;

	angle = 0;
	if (game->keys.right)
		angle -= ROT_SPEED;
	if (game->keys.left)
		angle += ROT_SPEED;
	if (angle == 0)
		return ;
	apply_rotation(game, cos(angle), sin(angle));
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
	if (keycode == KEY_E)
		trigger_interact(game);
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
