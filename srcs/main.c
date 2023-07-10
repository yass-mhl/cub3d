/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/10 18:08:51 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parsing(int ac, char **av, t_map *data, t_config **config)
{
	if (ac != 2)
		return (printf(ERROR_ARGS), free_data(data), free_config(*config),
			false);
	if (!check_cub_extension(av[1]))
		return (printf(ERROR_EXT), free_data(data), free_config(*config),
			false);
	if (!is_directory_is_valid(av[1]))
		return (printf(ERROR_DIR), free_data(data), free_config(*config),
			false);
	data->file = get_file(av[1]);
	if (!data->file)
		return (printf(ERROR_DIR), false);
	data->map = get_map(data->file);
	if (!data->map)
		return (false);
	if (!check_args(data) || !is_valid_map(data))
		return (free_data(data), free_config(*config), printf(ERROR_MAP),
			false);
	replace_spaces_with_one(data->map);
	set_config(data, *config);
	if (!check_config(*config))
		return (free_data(data), free_config(*config), printf("Error\n"),
			false);
	return (true);
}

static void	init_data(t_config **config, t_map **data)
{
	(*config)->no = NULL;
	(*config)->so = NULL;
	(*config)->we = NULL;
	(*config)->ea = NULL;
	(*config)->c = NULL;
	(*config)->f = NULL;
	(*config)->mlx = NULL;
	(*config)->pixelMap = NULL;
	(*config)->textures = NULL;
	(*data)->file = NULL;
	(*data)->map = NULL;
}

static int	initialize(t_config **config, t_map **data, int ac, char **av)
{
	*config = get_config();
	*data = malloc(sizeof(t_map));
	if (!(*data))
		return (printf(ERROR_MALLOC), 1);
	init_data(config, data);
	if (!parsing(ac, av, *data, config))
		return (1);
	(*config)->map = *data;
	return (0);
}
t_config *get_config(void)
{
	static t_config	*config = NULL;
	if (!config)
	{
		config = malloc(sizeof(t_config));
		if (!config)
			return (printf(ERROR_MALLOC), NULL);
	}
	return (config);
}

int	main(int ac, char **av)
{
	t_map		*data;
	t_config	*config;

	if (initialize(&config, &data, ac, av) != 0)
		return (1);
	if (!config->textures)
		config->textures = create_textures();
	if (!config->textures)
		return (printf("Failed to create textures\n"), 1);
	populate_textures(config, config->textures);
	config->pixelMap = raycast(config);
	render(config);
	return (0);
}
