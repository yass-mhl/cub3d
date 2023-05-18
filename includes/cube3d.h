# ifndef CUB3D_H
# define CUB3D_H


// Inclusion des bibliothèques standard nécessaires
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

 // Définition des constantes
 # define WINDOW_WIDTH 1920
 # define WINDOW_HEIGHT 1080
 # define MAX_SLICES 1024

// Définition des structures de données
typedef struct {
    char *no;
    char *so;
    char *we;
    char *ea;
    int player_pos_x;
    int player_pos_y;
    char player_orientation;
} t_config;

typedef struct	s_mlximg {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlximg;

typedef struct  s_slice
{
    int     height;
    int    	color;
    int     x;
    int     start;
    int     end;
}               t_slice;

typedef struct  s_scene
{
    t_slice **column;
	t_mlximg	mlx_img;
    int     nb_columns;
}               t_scene;

typedef struct s_map
{
    int width;
    int height;
    char **file;
    char **map;
}   t_map;

void        render(t_scene *scene);
char		**get_file(char *filename);
char        **get_map(char **map);
bool        is_valid_map(t_map *data);



// // Définition des structures de données
// typedef struct s_player
// {
//     float x;
//     float y;
//     float angle;
// } t_player;

// typedef struct s_map
// {
//     int width;
//     int height;
//     char **data;
// } t_map;

// // Déclaration des fonctions
// void parse_file(const char *filename, t_map *map, t_player *player);
// void raycast(t_map *map, t_player *player);
// void move_player(t_player *player, float dx, float dy);
// void render(t_map *map, t_player *player);

#endif // CUB3D_H
