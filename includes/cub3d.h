#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define SCREEN_W	1280
# define SCREEN_H	720

// macros
# define SCREEN_W	1280
# define SCREEN_H	720

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

// raycasting structures

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
} t_ray;

typedef struct s_draw
{
	int		tex_idx;
	int		ceiling_color;
	int		floor_color;
	int		tex_y;
	int		color;
	double	tex_step;
	double	tex_pos;
}	t_draw;



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

/* raycasting and rendering */
void	calc_wall_height(t_ray *ray);
int		select_texture(t_ray *ray);
void    draw_wall_column(t_game *game, t_ray *ray, int x, int tex_idx);
int     get_texel_color(t_img *tex, int tex_x, int tex_y);
void	render_frame(t_game *game);

/* player*/
void	init_player(t_game *game);
int		key_hook(int keycode, t_game *game);
int		mouse_hook(int x, int y, t_game *game);
int		close_hook(t_game *game);

/*2d engine*/
void	draw_minimap(t_game *game);
void	put_pixel_safe(t_img *img, int x, int y, int color);

/*initialization*/
void	mlx_pixel_put_to_image(t_img *img, int x, int y, int color);

#endif