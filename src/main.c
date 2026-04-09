#include "cub3d.h"

void	error_exit(char *message)
{
	printf("Error : %s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error_exit("Only 2 arguments are needed");
	if (!ft_strnstr(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		error_exit("The map file must be a .cub file !!");
	t_scene	scene;
	int		i;

	init_scene(&scene);
	parse_config(av[1], &scene);

	/* DEBUG START - remove before final submission */
	i = 0;
	printf("Map [%d x %d] | Spawn: (%d,%d) dir:%c\n",
		scene.map.width, scene.map.height,
		scene.spawn.x, scene.spawn.y, scene.spawn.direction);
	while (i < scene.map.height)
		printf("%s\n", scene.map.grid[i++]);
	/* DEBUG END */

	init_mlx(&scene);
	return (0);
}