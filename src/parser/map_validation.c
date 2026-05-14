/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:15:45 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/14 14:17:50 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(t_scene *scene)
{
	int	i;
	int	len;
	int	max_width;

	max_width = 0;
	i = -1;
	while (++i < scene->map.height)
	{
		len = ft_strlen(scene->map.grid[i]);
		if (len > 0 && scene->map.grid[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
	}
	return (max_width);
}

static void	pad_row(t_scene *scene, int i, int max_width)
{
	int		len;
	char	*padded;

	len = ft_strlen(scene->map.grid[i]);
	if (len > 0 && scene->map.grid[i][len - 1] == '\n')
		len--;
	padded = ft_calloc(max_width + 1, sizeof(char));
	if (!padded)
		error_exit("malloc failed");
	ft_memcpy(padded, scene->map.grid[i], len);
	while (len < max_width)
		padded[len++] = ' ';
	free(scene->map.grid[i]);
	scene->map.grid[i] = padded;
}

void	normalize_map(t_scene *scene)
{
	int	i;
	int	max_width;

	max_width = get_max_width(scene);
	scene->map.width = max_width;
	i = -1;
	while (++i < scene->map.height)
		pad_row(scene, i, max_width);
}

static void	add_char(t_scene *scene, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (scene->spawn.found)
			error_exit("Multiple player spawns found");
		scene->spawn.found = 1;
		scene->spawn.x = x;
		scene->spawn.y = y;
		scene->spawn.direction = c;
	}
}

void	map_validation(t_scene *scene)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < scene->map.height)
	{
		j = -1;
		len = ft_strlen(scene->map.grid[i]);
		while (++j < len)
		{
			if (scene->map.grid[i][j] == '\n')
				continue ;
			if (scene->map.grid[i][j] != '1' && scene->map.grid[i][j] != '0'
				&& scene->map.grid[i][j] != 'N' && scene->map.grid[i][j] != 'S'
				&& scene->map.grid[i][j] != 'E' && scene->map.grid[i][j] != 'W'
				&& scene->map.grid[i][j] != 'D' && scene->map.grid[i][j] != 'O')
				error_exit("Invalid character in map");
			add_char(scene, scene->map.grid[i][j], j, i);
		}
	}
	if (!scene->spawn.found)
		error_exit("No player spawn found in map");
	normalize_map(scene);
	check_flood(scene);
}
