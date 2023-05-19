/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/19 15:09:08 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

static bool parsing(int ac, char **av, t_map *data, t_config *config)
{
	if (ac != 2)
		return (printf("Error\n"), false);
	if (!check_cub_extension(av[1]))
		return (printf("Error\n"), false);
	if (!is_directory_is_valid(av[1]))
		return (printf("Error\n"), false);
	data->file = get_file(av[1]);
	data->map = get_map(data->file);
	if (!data->map)
		return (printf("erreur data->map"), false);
	if (!check_args(data) || !is_valid_map(data))
		return (printf("Error\n"), false);
	replace_spaces_with_one(data->map);
	config = set_config(data);
	if (!check_config(config))
		return (printf("Error\n"), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_map data;
	t_config *config;
	config = NULL;
	if (!parsing(ac, av, &data, config))
		return (0);
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n",data.map[i]);
		i++;
	}
	// render(NULL); 
	return (0);
}
