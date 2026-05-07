/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:48:05 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/07 15:40:03 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *message)
{
	printf("Error : %s\n", message);
	exit(1);
}

static int	game_loop(t_game *game)
{
	update_player(game);
	render_frame(game);
	draw_minimap(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		error_exit("Only 2 arguments are needed");
	if (!ft_strnstr(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		error_exit("The map file must be a .cub file !!");
	ft_memset(&game, 0, sizeof(t_game));
	init_scene(&game.scene);
	parse_config(av[1], &game.scene);
	init_mlx(&game);
	init_player(&game);
	mlx_loop_hook(game.mlx.mlx, game_loop, &game);
	mlx_loop(game.mlx.mlx);
	free_scene(&game.scene);
	return (0);
}
