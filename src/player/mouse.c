/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:56:15 by halzamma          #+#    #+#             */
/*   Updated: 2026/04/27 14:56:15 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_by_angle(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = old_dir_x * cos(-angle) - p->dir_y * sin(-angle);
	p->dir_y = old_dir_x * sin(-angle) + p->dir_y * cos(-angle);
	old_plane_x = p->plane_x;
	p->plane_x = old_plane_x * cos(-angle) - p->plane_y * sin(-angle);
	p->plane_y = old_plane_x * sin(-angle) + p->plane_y * cos(-angle);
}

int	mouse_hook(int x, int y, t_game *game)
{
	int			delta_x;

	(void)y;
	delta_x = x - SCREEN_W / 2;
	if (delta_x == 0)
		return (0);
	rotate_by_angle(&game->player, delta_x * -0.002);
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, SCREEN_W / 2, SCREEN_H / 2);
	return (0);
}