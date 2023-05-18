#ifndef CUB3D_H
# define CUB3D_H
# define MAX_SLICES 1024

// Inclusion des bibliothèques standard nécessaires
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

// Définition des structures de données

typedef struct s_map
{
	int		width;
	int		height;
	char	**file;
	char	**map;
}			t_map;

typedef struct
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		player_pos_x;
	int		player_pos_y;
	char	player_orientation;
	t_map	*map;
}			t_config;

typedef struct s_check
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int 	f;
	int		c;
}			t_check;

typedef struct s_slice
{
	int		height;
	char	*texture;
	int		x;
}			t_slice;

typedef struct s_scene
{
	t_slice	*slices;
	int		num_slices;
}			t_scene;

void		render(t_scene *scene);

// Déclaration des fonctions de parsing
char		**get_file(char *filename);
char		**get_map(char **map);
int			main(int ac, char **av);
bool		is_valid_map(t_map *data);
int			is_space(char c);
int			check_cross(char **map, int i, int j);
int			count_lines(const char *filename);
bool 		check_args(t_map *data);

// Déclaration des fonctions de free
void		ft_free_all_tab(char **tab, int index);
// Définition des constantes
// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGHT 600

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
