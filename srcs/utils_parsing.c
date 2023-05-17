/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:23:39 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 15:40:31 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_space(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	check_cross(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
		return (0);
	if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' '
		|| map[i - 1][j] == ' ')
		return (0);
	return (1);
}
