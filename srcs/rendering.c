# include "cube3d.h"

//void draw_slice(t_slice slice, int column, t_scene *scene) 
//{
//    // code pour dessiner une tranche ici...
//}

//void draw_scene(t_scene *scene) 
//{
//	int column;

//	column = 0;
//    while (column < scene->num_slices) 
//	{
//        draw_slice(scene->slices[column], column, scene);
//		column++
//    }
//}

// Cette fonction est appelée pour commencer le rendu
void render(t_scene *scene) 
{
    // code pour préparer le rendu ici...
	(void) scene;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
    //draw_scene(scene);

    // code pour finaliser le rendu ici...
}
