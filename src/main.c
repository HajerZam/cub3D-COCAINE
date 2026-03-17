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
	init_scene(&scene);
	parse_config(av[1], &scene);
	parse_map(av[1], &scene);
	init_mlx(&scene);
	return (0);
}