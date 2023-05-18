/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/18 18:15:40 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_map data;
	t_config *config;

	data.file = get_file("test.cub");
	data.map = get_map(data.file);
	if (!data.map)
		return (printf("erreur data.map"), 0);
	// printf("i = %d : %d\n", 0, data.map[0][0]);
	if (!check_args(&data) || !is_valid_map(&data))
		return (printf("Error\n"), 0);
	replace_spaces_with_one(data.map);
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n",data.map[i]);
		i++;
	}

	config = set_config(&data);
	// printf("config->no = %s\n", config->no);
	// printf("config->y = %d\n", config->player_pos_y);
	// render(NULL); 
	return (0);
}
