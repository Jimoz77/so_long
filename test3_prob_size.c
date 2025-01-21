#include "so_long.h"
#include <stdio.h>

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dest;
    if (data->addr)
    {
        dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)dest = color;
    }
    return ;
    
}
bool is_valid_move(t_map *map, bool **visited, int x, int y)
{
    return (x >= 0 && y >= 0 && x < map->width && y < map->height && map->map_data[y][x] != '1' && !visited[y][x]);
}

bool    dfs(t_map *map, bool **visited, int x, int y)
{
    int new_x;
    int new_y;
    int i = 0;
    static bool exit = false;
    if (map->map_data[y][x] == 'E')
        exit = true;
    if (map->map_data[y][x] == 'C' && exit == true)
        return (true);
    visited[y][x] = true;
    point directions[4] = {{1, 0}, {-1, 0}, {0,1}, {0,-1}};
    while (i < 4)
    {
        new_x = x + directions[i].x;
        new_y = y + directions[i].y;
        if (is_valid_move(map, visited, new_x, new_y))
            if (dfs(map, visited, new_x, new_y))
                return (true);
        i++;
    }
    return (false);    
}
bool find_player(t_map *map, int *x, int *y)
{
    int i = 0;
    int j;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            if(map->map_data[i][j] == 'P')
            {
                *x = j;
                *y = i;
                return (true);
            }
            j++;
        }
        i++;
    }
    return (false);
}
bool is_map_solvable(t_map *map)
{
    int player_x;
    int player_y;
    bool result;
    int i = 0;
    int j;
    if (!find_player(map, &player_x, &player_y))
        return (false);
    bool **visited = (bool **)malloc(map->height * sizeof(bool *));
    if (!visited)
        return (false);
    while (i < map->height)
    {
        visited[i] = (bool *)malloc(map->width * sizeof(bool));
        if (!visited[i])
        {
            while (i-- > 0)
                free(visited[i]);
            free(visited);
            return(false);
        }
        j = 0;
        while (j < map->width)
        {
            visited[i][j] = false;
            j++;
        }
        i++;
    }
    result = dfs(map, visited, player_x, player_y);
    i = 0;
    while (i < map->height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    return (result);
}
int check_map_corners(t_map *map)
{
    int x = 0;
    int y = 0;
    int y_max;
    while (x < (map->width - 1))
    {
        if (map->map_data[0][x] != '1')
            return (0);
        x++;
    }
   while(y < map->height - 1)
    {
        if (map->map_data[y][0] != '1')
            return (0);
        y++;
    }
    y_max = y;
    x--;
    while (y >= 0)
    {
        if (map->map_data[y][x] != '1')
            return (0);
        y--;
    }
     while (x >= 0)
    {
        if (map->map_data[y_max][x] != '1')
            return (0);
        x--;
    }
    return (1);
}

void draw_sprite(t_data *img, t_sprite *sprite, int start_x, int start_y, int sprite_x, int sprite_y, int sprite_width, int sprite_height, int zoom_factor)
{
    int x;
    int y;
    char *pixel;
    int color;
    int dy;
    int dx;
    y = 0;
    while (y <= sprite_height)
    {
        x = 0;
        while (x <= sprite_width)
        {
            // Vérifiez que les coordonnées sont dans les limites de l'image source
            if ((sprite_y + y) < sprite->height && (sprite_x + x) < sprite->width)
            {
                pixel = sprite->addr + ((sprite_y + y) * sprite->width + (sprite_x + x)) * 4;
                color = *(unsigned int *)pixel;
                dy = 0;
                while ( dy < zoom_factor) // Loop to scale the sprite vertically
                {
                    dx = 0;
                    while (dx < zoom_factor) // Loop to scale the sprite horizontally
                    {
                        // Vérifiez que les coordonnées sont dans les limites de l'image destination
                        if ((start_y + y * zoom_factor + dy) < 1080 && (start_x + x * zoom_factor + dx) < 1920)
                        {
                            my_mlx_pixel_put(img, start_x + x * zoom_factor + dx, start_y + y * zoom_factor + dy, color);
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
}

void draw_map(t_map *map, t_data *img, t_sprite *sprite, int zoom_factor)
{
    int x;
    int y;
    int pixel_x;
    int pixel_y;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            pixel_x = x * TILE_SIZE * zoom_factor; // Multiply by zoom_factor to account for the scaling
            pixel_y = y * TILE_SIZE * zoom_factor; // Multiply by zoom_factor to account for the scaling
            if (map->map_data[y][x] == '1')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_WALL_X, SPRITE_WALL_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            else if (map->map_data[y][x] == '0')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_FLOOR_X, SPRITE_FLOOR_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            else if (map->map_data[y][x] == 'P')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_PLAYER_X, SPRITE_PLAYER_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            else if (map->map_data[y][x] == 'E')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_EXIT_X, SPRITE_EXIT_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            else if (map->map_data[y][x] == 'C')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_COIN_X, SPRITE_COIN_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            else if (map->map_data[y][x] == 'D')
                draw_sprite(img, sprite, pixel_x, pixel_y, SPRITE_EXIT_DONE_X, SPRITE_EXIT_DONE_Y, TILE_SIZE, TILE_SIZE, zoom_factor);
            x++;
        }
        y++;
    }
}
int move_player(t_map *map, int keycode)
{
    int x;
    int y;
    int new_x;
    int new_y;
    static int move = -1;
    static int coin_wallet = 0;

    // Trouver la position actuelle du joueur
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->map_data[y][x] == 'P')
                break;
            x++;
        }
        if (x < map->width && map->map_data[y][x] == 'P')
            break;
        y++;
    }
    if (x >= map->width || y >= map->height)
        return 0;
    new_x = x;
    new_y = y;

    // Déplacer le joueur selon l'input
    if (keycode == 119) // 'w'
        new_y--;
    else if (keycode == 115) // 's'
        new_y++;
    else if (keycode == 97)  // 'a'
        new_x--;
    else if (keycode == 100) // 'd'
        new_x++;

    // Vérifie que les nouvelles coordonnées sont dans les limites de la carte
    if (new_x >= 0 && new_x < map->width && new_y >= 0 && new_y < map->height)
    {
        if (map->map_data[new_y][new_x] != '1' && map->map_data[new_y][new_x] != 'E')
        {
            if (map->map_data[new_y][new_x] == 'C')
            {
                coin_wallet++;
            }
            map->map_data[y][x] = '0';
            map->map_data[new_y][new_x] = 'P';
            move++;
            ft_printf("mouvements : %d\n", move);
            return 1;
        }
        else if (map->map_data[new_y][new_x] == 'E' && coin_wallet > 0) // Autorise l'accès à 'E' seulement si au moins une pièce est ramassée
        {
            map->map_data[y][x] = '0';
            map->map_data[new_y][new_x] = 'D';
            move++;
            ft_printf("mouvements : %d\n", move);
            return 1;
        }
        return 0;
    }
    return 0;
}



int key_input(int keycode, void *param)
{
    t_params *params = (t_params *)param;
    int change = 0;
    if (keycode == 53 || keycode == 65307)
    {
        mlx_destroy_window(params->mlx_ptr, params->win_ptr);
        exit(0);
    }
    change = move_player(params->map, keycode);
    if(change == 1)
    {
        draw_map(params->map, params->img, params->sprite, params->zoom);
        mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->img->img, 0, 0);
    }

    return (0);
}


int close_win_cross(void *param)
{
    t_params *params = (t_params *)param;
    mlx_destroy_window(params->mlx_ptr, params->win_ptr);
    exit(0);
    return (0);
}

t_sprite *load_sprite(void *mlx, char *file_path)
{
    t_sprite *sprite;
    sprite = (t_sprite *)malloc(sizeof(t_sprite));
    if (!sprite)
        return (NULL);
    sprite->img = mlx_xpm_file_to_image(mlx, file_path, &sprite->width, &sprite->height);
    if (!sprite->img)
    {
        free(sprite);
        return (NULL);
    }
    sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel, &sprite->line_length, &sprite->endian);
    return (sprite);
}

t_map *read_map(char *file_name)
{
    int fd;
    char *line;
    t_map *map;
    int i;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (NULL);
    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->height = 0;
    while ((line = get_next_line(fd)))
    {
        free(line);
        map->height++;
    }
    map->map_data = (char **)malloc(sizeof(char *) * map->height);
    if (!map->map_data)
    {
        free(map);
        return (NULL);
    }
    close(fd);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        free(map->map_data);
        free(map);
        return (NULL);
    }
    i = 0;
    while ((line = get_next_line(fd)))
    {
        map->map_data[i] = line;
        i++;
    }
    if (map->height > 0)
        map->width = ft_strlen(map->map_data[0]);
    else
        map->width = 0;
    close(fd);
    return (map);
}


int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img = {0};
    t_map *map;
    t_sprite *sprite;
    t_params params = {0}; // Crée une instance de t_params
    int checked = 0;
    int zoom_factor = 1; 

    mlx = (void *)mlx_init();
    if (!mlx)
    {
        ft_printf("Erreur lors de l'initialisation de mlx\n");
        return (1);
    }
    mlx_win = mlx_new_window(mlx, 1920, 1080, "slime buck");
    if (!mlx_win)
    {
        ft_printf("Erreur lors de la création de la fenêtre\n");
        return (1);
    }
    img.img = mlx_new_image(mlx, 1920, 1080);
    if (!img.img)
    {
        ft_printf("Erreur lors de la création de l'image\n");
        return (1);
    }
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    if (!img.addr)
    {
        ft_printf("Erreur lors de l'accès aux données de l'image\n");
        return (1);
    }
    sprite = load_sprite(mlx, "spritesheet.so_long.xpm");
    if (!sprite)
        return (1);
    map = read_map("map_wide.ber");
    if ((check_map_corners(map) == 0 && checked == 0) || is_map_solvable(map) == 0)
    {
        ft_printf("LA MAP N'EST PAS FERMÈE, INCOMPLÈTE OU INSOLVABLE\n");
        return (0);
    }
    checked = 1;

    //printf("%d\n", is_map_solvable(map));
    // Initialiser les paramètres
    params.img = &img;
    params.map = map;
    params.sprite = sprite;
    params.mlx_ptr = mlx;
    params.win_ptr = mlx_win;
    params.zoom = zoom_factor;

    draw_map(map, &img, sprite, zoom_factor); 
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    
    mlx_key_hook(mlx_win, key_input, &params); // Passe l'adresse des paramètres
    mlx_hook(mlx_win, 33, (1L << 17), close_win_cross, mlx);
    mlx_loop(mlx);

    return 0;
}


