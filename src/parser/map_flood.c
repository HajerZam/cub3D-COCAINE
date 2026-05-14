/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:18:19 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/14 14:18:19 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**copy_grid(t_scene *scene)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (scene->map.height + 1));
	if (!copy)
		error_exit("malloc failed");
	i = -1;
	while (++i < scene->map.height)
	{
		copy[i] = ft_strdup(scene->map.grid[i]);
		if (!copy[i])
			error_exit("malloc failed");
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static void	flood_fill(char **grid, t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		error_exit("Map is not closed (out of bounds)");
	if (grid[y][x] == ' ')
		error_exit("Map is not closed (reachable space)");
	if (grid[y][x] == '1' || grid[y][x] == 'D' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood_fill(grid, map, x + 1, y);
	flood_fill(grid, map, x - 1, y);
	flood_fill(grid, map, x, y + 1);
	flood_fill(grid, map, x, y - 1);
}

void	check_flood(t_scene *scene)
{
	char	**copy;

	copy = copy_grid(scene);
	flood_fill(copy, &scene->map, scene->spawn.x, scene->spawn.y);
	free_grid(copy);
}
