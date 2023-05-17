/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 14:09:07 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	// t_map data;

	// data.map = get_file("test.cub");
	// // data.map = get_map(data.file);
	// if (!data.map)
	// 	return (printf("erreur data.map0"), 0);
	// // while (*data.map)
	// // {
	// // 	printf("%s\n", *data.map);
	// // 	data.map++;
	// // }
	// if (!is_valid_map(&data))
	// 	return (printf("Error\n"), 0);
	// return (0);
	render(NULL); 
	return (0);
}
