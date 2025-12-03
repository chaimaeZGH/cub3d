#include "cube.h"

void init_map(t_game *g)
{
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1},  
    {1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,0,1,1,1,0,0,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    int i = 0;
    int j;
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            g->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}

void init_player(t_player *player)
{
    player->x = 5.5;
    player->y = 5.5;
    player->dir_x = -1.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.66;
    player->move_speed = 0.05;
    player->rot_speed = 0.03;
}

void init_ray(t_ray *ray, t_game *g, int x)
{
    ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    ray->dir_x = g->player.dir_x + g->player.plane_x * ray->camera_x;
    ray->dir_y = g->player.dir_y + g->player.plane_y * ray->camera_x;
    
    ray->map_x = (int)g->player.x;
    ray->map_y = (int)g->player.y;
    
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

void calculate_step(t_ray *ray, t_game *g)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (g->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - g->player.x) * ray->delta_dist_x;
    }
    
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (g->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - g->player.y) * ray->delta_dist_y;
    }
}

void perform_dda(t_ray *ray, t_game *g)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (g->map[ray->map_y][ray->map_x] > 0)
            ray->hit = 1;
    }
}

void calculate_wall_distance(t_ray *ray, t_game *g)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - g->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - g->player.y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void draw_vertical_line(t_game *g, int x, int draw_start, int draw_end, uint32_t color)
{
    int y = draw_start;
    
    while (y < draw_end)
    {
        if (y >= 0 && y < SCREEN_HEIGHT)
            mlx_put_pixel(g->img, x, y, color);
        y++;
    }
}

void draw_wall(t_game *g, int x, t_ray *ray)
{
    int line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    uint32_t color;
    if (ray->side == 0)
    {
        color = 0x000880FF;
    }
    else
    {
        color = 0x088000FF;
    }
    draw_vertical_line(g, x, 0, draw_start, 0x333333FF);
    draw_vertical_line(g, x, draw_start, draw_end, color);
    draw_vertical_line(g, x, draw_end, SCREEN_HEIGHT, 0x666666FF);
}



void draw_ceiling_and_floor(t_game *G)
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        uint32_t color_c = ((uint32_t)G->my_map->ceil->r << 24) | ((uint32_t)G->my_map->ceil->g << 16) | ((uint32_t)G->my_map->ceil->b << 8) | (uint32_t)255;
        draw_vertical_line(G, x, 0, SCREEN_HEIGHT / 2, color_c);
        uint32_t color_f = ((uint32_t)G->my_map->floor->r << 24) | ((uint32_t)G->my_map->floor->g << 16) | ((uint32_t)G->my_map->floor->b << 8) | (uint32_t)255;
        draw_vertical_line(G, x, SCREEN_HEIGHT / 2, SCREEN_HEIGHT, color_f);
        x++;
    }
}

void cast_rays(t_game *g)
{
    draw_ceiling_and_floor(g);
    int x = 0;
    t_ray ray;
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, g, x);
        calculate_step(&ray, g);
        perform_dda(&ray, g);
        calculate_wall_distance(&ray, g);
        draw_textured_wall(g, x, &ray);
        x++;
    }
}

void rotate_player(t_player *p, double angle)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
    p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
    p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void handle_movement(t_game *g)
{
    double new_x;
    double new_y;
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
    {
        new_x = g->player.x + g->player.dir_x * g->player.move_speed;
        new_y = g->player.y + g->player.dir_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
    {
        new_x = g->player.x - g->player.dir_x * g->player.move_speed;
        new_y = g->player.y - g->player.dir_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
    {
        new_x = g->player.x - g->player.plane_x * g->player.move_speed;
        new_y = g->player.y - g->player.plane_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
    {
        new_x = g->player.x + g->player.plane_x * g->player.move_speed;
        new_y = g->player.y + g->player.plane_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
        rotate_player(&g->player, g->player.rot_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
        rotate_player(&g->player, -g->player.rot_speed);
}

void loop_hook(void *param)
{
    t_game *g = param;

    handle_movement(g);

    memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    cast_rays(g);
}

void lll()
{
	system ("leaks Cube3d");
}
t_pars	*map_fill(int argc, char **argv)
{
    t_pars	*my_map;
    char	*line;
    int		s;

    if (argc < 2 || argc > 4)
		return (printf("erreur in args\n"), NULL);
	if (ft_count(argv[1]) > 1)
		return (printf("erreur in file name\n"), NULL);
	if (!chck_cub(argv[1]))
		return (printf("erreur in file name only '*.cub'\n"), NULL);
	s = open(argv[1], O_RDONLY);
	if (s < 0)
		return (printf("erreur in oprning file\n"), NULL);
	my_map = malloc(sizeof(t_pars));
	if(!my_map)
		return 0;
	my_map->ea = NULL;
	my_map->no = NULL;
	my_map->so = NULL;
	my_map->we = NULL;
	my_map->map = NULL;
	my_map->stop = false;
	my_map->ceil = NULL;
    my_map->floor = NULL;
	line = get_next_line(s);
	while (line != NULL)
	{
		while (line != NULL && chack_empty_line(line) == 1)
		{
			free(line);
			if (my_map != NULL && my_map->map != NULL)
				my_map->stop = true;
			line = get_next_line(s);
		}
		if (fill_mapst(line, my_map) == 0)
		{
			free(line);
			printf("erreur in map\n");
			return (NULL);
		}
		free(line);
		line = get_next_line(s);
	}
	free(line);
	if (check_map(my_map->map) == 0)
	{
		printf("map form is not corect\n");
		free_mymap(my_map);
		my_map = NULL; 
	}
	fill_map(my_map);
	if(my_map == NULL)
		return (printf("faild to malloc new map"), NULL);
    return (my_map);
}

int fill_tex(t_pars	*my_map, t_game *g)
{
    g->texture_south= mlx_load_png(my_map->so);
    if (!g->texture_south)
        return (1);
    g->img_wall_south = mlx_texture_to_image(g->mlx, g->texture_south);
	if (!(g->img_wall_south))
		return (1);
    g->texture_west= mlx_load_png(my_map->we);
    if (!g->texture_west)
        return (1);
    g->img_wall_west = mlx_texture_to_image(g->mlx, g->texture_west);
	if (!(g->img_wall_west))
		return (1);
    return 0;
}
int    fill_textur(t_pars	*my_map, t_game *g)
{
    g->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    if (!g->mlx)
        return (1);
    g->texture_east= mlx_load_png(my_map->ea);
    if (!g->texture_east)
        return (1);
    g->img_wall_east = mlx_texture_to_image(g->mlx, g->texture_east);
	if (!(g->img_wall_east))
		return (1);
    g->texture_north= mlx_load_png(my_map->no);
    if (!g->texture_north)
        return (1);
    g->img_wall_north = mlx_texture_to_image(g->mlx, g->texture_north);
	if (!(g->img_wall_north))
		return (1);
    if(fill_tex(my_map, g) == 1)
        return 1;
    return 0;
}

void    free_texturs(t_game *g)
{
    mlx_delete_texture(g->texture_east);
    mlx_delete_texture(g->texture_west);
    mlx_delete_texture(g->texture_north);
    mlx_delete_texture(g->texture_south);
    mlx_delete_image(g->mlx, g->img_wall_east);
    mlx_delete_image(g->mlx, g->img_wall_west);
    mlx_delete_image(g->mlx, g->img_wall_north);
    mlx_delete_image(g->mlx, g->img_wall_south);
    mlx_delete_image(g->mlx, g->img);
    mlx_terminate(g->mlx);
}
int main(int argc, char **argv)
{
    t_game g;
	g.my_map = map_fill(argc, argv);
    if(g.my_map == NULL)
        return 1;
    // g.map = my_map->map;
    init_map(&g);
    init_player(&g.player);
    if (fill_textur(g.my_map,&g) == 1)
        return 1;
    g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g.mlx, g.img, 0, 0);
    atexit(lll);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
    free_mymap(g.my_map);
    free_texturs(&g);
    return (0);
}
