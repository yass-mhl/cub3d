/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/26 05:52:05 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

static bool parsing(int ac, char **av, t_map *data, t_config **config)
{
	if (ac != 2)
		return (printf(ERROR_ARGS), false);
	if (!check_cub_extension(av[1]))
		return (printf(ERROR_EXT), false);
	if (!is_directory_is_valid(av[1]))
		return (printf(ERROR_DIR), false);
	data->file = get_file(av[1]);
	data->map = get_map(data->file);
	if (!data->map)
		return (false);
	if (!check_args(data) || !is_valid_map(data))
		return (free_data(data), printf(ERROR_MAP), false);
	replace_spaces_with_one(data->map);
	*config = set_config(data);
	if (!check_config(*config))
		return (free_data(data), free_config(*config),  printf("Error\n"), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_map data;
	t_config *config;
	
	config = malloc(sizeof(t_config));
	if (!config)
		return (0);
	if (!parsing(ac, av, &data, &config))
		return (0);
	// int i = 0;
	// while (data.map[i])
	// {
	// 	printf("%s\n",data.map[i]);
	// 	i++;
	// }
	// render(NULL);
	free_config(config);
	free_data(&data);
	return (0);
}
