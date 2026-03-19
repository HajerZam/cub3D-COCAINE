#include "cub3d.h"

void    init_scene_config(t_config *config)
{
    config->has_no = 0;
    config->has_so = 0;
    config->has_we = 0;
    config->has_ea = 0;
    config->has_f = 0;
    config->has_c = 0;
}

void    init_scene_parser(t_parser *parser)
{
    parser->in_map = 0;
    parser->map_started = 0;
    parser->map_ended = 0;
    parser->row = 0;
    parser->col = 0;
}

void    init_scene_spawn(t_spawn *spawn)
{
    spawn->row = -1;
    spawn->col = -1;
    spawn->dir = -1;
}

void    init_scene(t_scene *scene)
{
    scene->config.no_path = NULL;
    scene->config.so_path = NULL;
    scene->config.we_path = NULL;
    scene->config.ea_path = NULL;
    scene->config.floor.r = -1;
    scene->config.floor.g = -1;
    scene->config.floor.b = -1;
    scene->config.ceiling.r = -1;
    scene->config.ceiling.g = -1;
    scene->config.ceiling.b = -1;
    scene->map.grid = NULL;
    scene->map.height = 0;
    scene->map.width = 0;
    init_scene_spawn(&scene->spawn);
    init_scene_parser(&scene->parser);
    init_scene_config(&scene->config);
}



