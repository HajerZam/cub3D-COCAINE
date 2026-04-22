#include "cub3d.h"

void	error_exit(char *message)
{
	printf("Error : %s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		i;

	if (ac != 2)
		error_exit("Only 2 arguments are needed");
	if (!ft_strnstr(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		error_exit("The map file must be a .cub file !!");
	init_scene(&game.scene);
	parse_config(av[1], &game.scene);
	/* DEBUG START - remove before final submission */
	i = 0;
	printf("Map [%d x %d] | Spawn: (%d,%d) dir:%c\n",
		game.scene.map.width, game.scene.map.height,
		game.scene.spawn.x, game.scene.spawn.y, game.scene.spawn.direction);
	while (i < game.scene.map.height)
		printf("%s\n", game.scene.map.grid[i++]);
	/* DEBUG END */
	init_mlx(&game);
	free_scene(&game.scene);
	return (0);
}
