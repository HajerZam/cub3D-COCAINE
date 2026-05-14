/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halzamma <halzamma@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:54:25 by halzamma          #+#    #+#             */
/*   Updated: 2026/05/14 19:07:11 by halzamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static char	*dup_strip(char *s)
{
	char	*res;
	int		len;

	res = ft_strdup(s);
	len = ft_strlen(res);
	if (len > 0 && res[len - 1] == '\n')
		res[len - 1] = '\0';
	return (res);
}

static void	parse_texture(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !scene->config.has_no++)
		scene->config.no_path = dup_strip(skip_spaces(line + 3));
	else if (ft_strncmp(line, "SO ", 3) == 0 && !scene->config.has_so++)
		scene->config.so_path = dup_strip(skip_spaces(line + 3));
	else if (ft_strncmp(line, "WE ", 3) == 0 && !scene->config.has_we++)
		scene->config.we_path = dup_strip(skip_spaces(line + 3));
	else if (ft_strncmp(line, "EA ", 3) == 0 && !scene->config.has_ea++)
		scene->config.ea_path = dup_strip(skip_spaces(line + 3));
	else if (ft_strncmp(line, "DC ", 3) == 0 && !scene->config.has_do++)
		scene->config.do_path = dup_strip(skip_spaces(line + 3));
	else if (ft_strncmp(line, "DO ", 3) == 0 && !scene->config.has_dop++)
		scene->config.dop_path = dup_strip(skip_spaces(line + 3));
	else
		error_exit("Duplicate or unknown texture identifier");
}

static int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DC ", 3) == 0
		|| ft_strncmp(line, "DO ", 3) == 0);
}

void	parse_identifier(char *line, t_scene *scene)
{
	char	*val;

	if (is_texture_line(line))
		parse_texture(line, scene);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (scene->config.has_f)
			error_exit("Duplicate F identifier");
		val = skip_spaces(line + 2);
		parse_color(val, &scene->config.floor);
		scene->config.has_f = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (scene->config.has_c)
			error_exit("Duplicate C identifier");
		val = skip_spaces(line + 2);
		parse_color(val, &scene->config.ceiling);
		scene->config.has_c = 1;
	}
	else
		error_exit("Unknown identifier in config");
}
