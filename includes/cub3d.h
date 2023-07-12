/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:43:46 by gansard           #+#    #+#             */
/*   Updated: 2023/07/11 16:04:12 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Inclusion des bibliothèques standard nécessaires
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// Definition des macros

// Définition des constantes
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define KEYW 119
# define KEYS 115
# define KEYA 97
# define KEYD 100
# define KEYLEFT 65361
# define KEYRIGHT 65363
# define KEY_ESCAPE 65307
# define ROTSPEED 0.05
# define MOVESPEED 0.2

// Définition des messages d'erreur
# define ERROR_ARGS "Error\n: wrong number of arguments\n"
# define ERROR_EXT "Error\n: extension\n"
# define ERROR_DIR "Error\n: invalid file/directory\n"
# define ERROR_MAP "Error\n: invalid map\n"
# define ERROR_MALLOC "Error\n: malloc failed, je suis désolé..."

// Définition des structures de données
typedef struct s_map
{
	int			width;
	int			height;
	char		**file;
	char		**map;
}				t_map;

typedef struct s_mlximg
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			hexa_c;
	int			hexa_f;
}				t_mlximg;

typedef struct s_config
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			hexa_f;
	int			hexa_c;
	int			h;
	int			w;
	double		p_pos_x;
	double		p_pos_y;
	char		player_orientation;
	double		dirx;
	double		diry;
	double		plane_x;
	double		plane_y;
	int			**pixelMap;
	int			**textures;
	void		*mlx_win;
	void		*mlx;
	t_mlximg	*mlx_img;
	t_map		*map;
}				t_config;

typedef struct s_rc
{
	int			iter_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		camera_x;
	int			**buffer;
	int			x;
	int			**texture;
}				t_rc;

typedef struct s_check
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_check;

// Déclaration des fonctions
char			**get_file(char *filename);
char			**get_map(char **map);
bool			is_valid_map(t_map *data);
int				is_space(char c);
int				check_cross(char **map, int i, int j);
int				count_lines(const char *filename);
bool			check_args(t_map *data);
void			ft_fill_check(t_check *check);
void			set_config(t_map *data, t_config *config);
char			*get_identifier(char **file, char *identifier);
double			get_pos(char **map, char pos);
void			replace_spaces_with_one(char **map);
int				ft_tablen(char **tab);
int				check_f_c(t_config *config);
bool			check_config(t_config *config);
int				check_commas(char *str);
int				is_directory_is_valid(char *file);
int				check_cub_extension(char *file);
int				**raycast(t_config *config);
void			render(t_config *config);
int				key_press(int keycode, void *param);
void			move(t_config *config, int keycode);
void			rotate(t_config *config, int keycode);
void			draw_scene(int **map, void *mlx, void *mlx_win,
					t_mlximg *mlx_img);
int				ft_exit(t_config *config);
t_rc			init_rc(t_config *config, int iter_x);
t_rc			update_rc(t_rc rc, t_config *config);
void			process_rc(t_rc *rc, t_config *config);
int				**draw_pixels(t_rc rc);
void			ft_free_all_tab(char **tab);
void			ft_free_all_tab_int(int **tab);
void			free_config(t_config *config);
void			free_data(t_map *data);
void			raycasting(t_config *config);
int				**allocateBuffer(void);
int				**create_textures(void);
void			populate_textures(t_config *config, int **texture);
int				check_path(char *path);
char			*get_identifier(char **file, char *identifier);
char			*ft_strtokstr(char *str, char *sep);
int				rgb_to_hex(char *rgb);
t_config		*get_config(void);

#endif // CUB3D_H
