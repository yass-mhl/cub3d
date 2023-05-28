#ifndef CUB3D_H
# define CUB3D_H

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

// Definition des macros

# define ERROR_ARGS "Error\n: wrong number of arguments"
# define ERROR_EXT "Error\n: extension"
# define ERROR_DIR "Error\n: invalid file/directory"
# define ERROR_MAP "Error\n: invalid map"

// Définition des structures de données

typedef struct s_map
{
	int			width;
	int			height;
	char		**file;
	char		**map;
}				t_map;

typedef struct
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			player_pos_x;
	int			player_pos_y;
	int			player_orientation;
	t_map		*map;
}				t_config;

typedef struct s_check
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_check;

typedef struct s_slice
{
	int			height;
	int			color;
	int			x;
	int			start;
	int			end;
}				t_slice;

typedef struct s_mlximg
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlximg;

typedef struct s_scene
{
	t_slice		**column;
	t_mlximg	mlx_img;
	int			nb_columns;
}				t_scene;

void			render(t_scene *scene);

// Déclaration des fonctions de parsing
char			**get_file(char *filename);
char			**get_map(char **map);
int				main(int ac, char **av);
bool			is_valid_map(t_map *data);
int				is_space(char c);
int				check_cross(char **map, int i, int j);
int				count_lines(const char *filename);
bool			check_args(t_map *data);
void			ft_fill_check(t_check *check);
t_config		*set_config(t_map *data);
char			*get_identifier(char **file, char *identifier);
int				get_pos(char **map, char pos);
void			replace_spaces_with_one(char **map);
int				ft_tablen(char **tab);
int				check_f_c(t_config *config);
bool			check_config(t_config *config);
int				check_commas(char *str);
int				is_directory_is_valid(char *file);
int				check_cub_extension(char *file);

// Déclaration des fonctions de free
void			ft_free_all_tab(char **tab, int index);
void			free_config(t_config *config);
void			free_data(t_map *data);
// Définition des constantes
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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
