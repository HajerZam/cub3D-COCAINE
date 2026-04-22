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
	int				x;
	int				y;
	enum e_cardinal	dir;
	int				found;
	char			direction;
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

typedef struct s_parser
{
	int	in_map;
	int	map_started;
	int	map_ended;
	int	row;
	int	col;
}	t_parser;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
	t_spawn		spawn;
	t_parser	parser;
}	t_scene;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_game
{
	t_scene		scene;
	t_player	player;
	t_mlx		mlx;
	t_img		textures[4];
}	t_game;

// freeall.c
void	free_scene(t_scene *scene);

// init.c
void	init_scene(t_scene *scene);
void	init_mlx(t_game *game);

// main.c
void	error_exit(char *message);

// parser/main_parse.c
void	parse_config(char *file_path, t_scene *scene);

// parser/parse_config.c
void	parse_identifier(char *line, t_scene *scene);
void	validate_config(t_scene *scene);

// parser/map_validation.c
void	map_validation(t_scene *scene);

#endif