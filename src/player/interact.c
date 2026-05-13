/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:14:51 by fepennar          #+#    #+#             */
/*   Updated: 2026/05/13 13:22:42 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	trigger_interact(t_game *game)
{
	double	interact_x;
	double	interact_y;
	int		mx;
	int		my;

	interact_x = game->player.x + game->player.dir_x * 0.5;
	interact_y = game->player.y + game->player.dir_y * 0.5;
	if (is_wall(game, interact_x, interact_y))
	{
		mx = (int)interact_x;
		my = (int)interact_y;
		if (game->scene.map.grid[my][mx] == 'D')
			game->scene.map.grid[my][mx] = 'O';
		else if (game->scene.map.grid[my][mx] == 'O')
			game->scene.map.grid[my][mx] = 'D';
	}
}
