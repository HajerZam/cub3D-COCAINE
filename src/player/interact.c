/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:14:51 by fepennar          #+#    #+#             */
/*   Updated: 2026/05/05 15:14:54 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    trigger_interact(t_game *game)
{
    double	interact_x;
    double	interact_y;

    interact_x = game->player.x + game->player.dir_x * 0.5;
    interact_y = game->player.y + game->player.dir_y * 0.5;
    if (is_wall(game, interact_x, interact_y))
    {
        int mx = (int)interact_x;
        int my = (int)interact_y;
        if (game->scene.map.grid[my][mx] == 'D')
            game->scene.map.grid[my][mx] = 'O';
        else if (game->scene.map.grid[my][mx] == 'O')
            game->scene.map.grid[my][mx] = 'D';
    }
}