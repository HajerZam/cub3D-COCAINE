#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

enum e_keys
{
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC = 65307
};

enum e_cardinal
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
}	t_color;

typedef struct s_spawn
{
	int				row;
	int				col;
	enum e_cardinal	dir;	
}	t_spawn;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
}	t_map;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_color	floor;
	t_color	ceiling;
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_f;
	int		has_c;
}	t_config;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
	t_spawn		spawn;
	t_parser	parser;
}	t_scene;

typedef struct s_parser
{
	int	in_map;
	int	map_started;
	int	map_ended;
	int	row;
	int	col;
}	t_parser;

#endif