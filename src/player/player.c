/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:01:24 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/13 14:35:01 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_ns(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	set_direction(t_game *game, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_dir_ns(game, dir);
	else if (dir == 'E')
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

void	init_player(t_game *game)
{
	t_spawn	*s;

	s = &game->scene.spawn;
	game->player.x = s->x + 0.5;
	game->player.y = s->y + 0.5;
	set_direction(game, s->direction);
}

int	is_wall(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= game->scene.map.height)
		return (1);
	if (mx < 0 || mx >= game->scene.map.width)
		return (1);
	return (game->scene.map.grid[my][mx] == '1'
		|| game->scene.map.grid[my][mx] == 'D');
}
