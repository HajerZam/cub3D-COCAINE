#include "cub3d.h"

static void	parse_color(char *str, t_color *color)
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

// Skips leading spaces and returns pointer to first non-space char
static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

// Strips trailing newline from a duplicated string
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

void	parse_identifier(char *line, t_scene *scene)
{
	char	*val;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (scene->config.has_no)
			error_exit("Duplicate NO identifier");
		scene->config.no_path = dup_strip(skip_spaces(line + 3));
		scene->config.has_no = 1;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (scene->config.has_so)
			error_exit("Duplicate SO identifier");
		scene->config.so_path = dup_strip(skip_spaces(line + 3));
		scene->config.has_so = 1;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (scene->config.has_we)
			error_exit("Duplicate WE identifier");
		scene->config.we_path = dup_strip(skip_spaces(line + 3));
		scene->config.has_we = 1;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (scene->config.has_ea)
			error_exit("Duplicate EA identifier");
		scene->config.ea_path = dup_strip(skip_spaces(line + 3));
		scene->config.has_ea = 1;
	}
	else if (ft_strncmp(line, "DO ", 3) == 0)
	{
		if (scene->config.has_do)
			error_exit("Duplicate DO identifier");
		scene->config.do_path = dup_strip(skip_spaces(line + 3));
		scene->config.has_do = 1;
	}
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

// Called after parsing to ensure all 6 identifiers were found
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
		error_exit("Missing DO texture");
	if (!scene->config.has_f)
		error_exit("Missing F (floor) color");
	if (!scene->config.has_c)
		error_exit("Missing C (ceiling) color");
}
