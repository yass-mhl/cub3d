/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/21 18:15:58 by gregoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

static bool parsing(int ac, char **av, t_map *data, t_config *config)
{
	if (ac != 2)
		return (printf("Error 1\n"), false);
	if (!check_cub_extension(av[1]))
		return (printf("Error 2\n"), false);
	if (!is_directory_is_valid(av[1]))
		return (printf("Error 3\n"), false);
	data->file = get_file(av[1]);
	data->map = get_map(data->file);
	if (!data->map)
		return (printf("erreur data->map"), false);
	if (!check_args(data) || !is_valid_map(data))
		return (printf("Error 4\n"), false);
	replace_spaces_with_one(data->map);
	config = set_config(data);
	if (!check_config(config))
		return (printf("Error 5\n"), false);
	return (true);
}

t_scene *init_scene()
{
	t_scene *scene;
	scene = malloc(sizeof(t_scene));
	if(!scene)
		return (printf("Error malloc scene\n"), NULL);
	scene->config = malloc(sizeof(t_config));
	if(!scene->config)
		return (printf("Error malloc scene->config\n"), NULL);
	scene->config->map = malloc(sizeof(t_map));
	if(!scene->config->map)
		return (printf("Error malloc scene->config->map\n"), NULL);
	return (scene);
}

int	main(int ac, char **av)
{
	
	t_scene *scene;
	scene = init_scene();
	if(!scene)
		return (1);
	if (!parsing(ac, av, scene->config->map, scene->config))
		return (2);
	int i = 0;
	while (scene->config->map->map[i])
	{
		printf("%s\n",scene->config->map->map[i]);
		i++;
	}
	render(scene); 
	return (0);
}
