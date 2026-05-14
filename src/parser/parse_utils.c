/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:23:07 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/14 14:23:07 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *str, t_color *color)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		error_exit("Invalid color format, expected R,G,B");
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		error_exit("Color value out of range [0,255]");
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
}

void	validate_config(t_scene *scene)
{
	if (!scene->config.has_no)
		error_exit("Missing NO texture");
	if (!scene->config.has_so)
		error_exit("Missing SO texture");
	if (!scene->config.has_we)
		error_exit("Missing WE texture");
	if (!scene->config.has_ea)
		error_exit("Missing EA texture");
	if (!scene->config.has_do)
		error_exit("Missing DC (closed door) texture");
	if (!scene->config.has_dop)
		error_exit("Missing DO (open door) texture");
	if (!scene->config.has_f)
		error_exit("Missing F (floor) color");
	if (!scene->config.has_c)
		error_exit("Missing C (ceiling) color");
}
