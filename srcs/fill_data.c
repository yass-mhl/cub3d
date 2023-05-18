/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:46:17 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/18 17:53:07 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char *ft_strtokstr(char *str, char *sep)
{
	int		i;
	int		index_sep;
	char	*tmp;
	char 	*res;

	i = 0;
	index_sep = ft_strstr(str, sep);
	if (index_sep == -1)
		return (NULL);
	index_sep += ft_strlen(sep);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - index_sep + 1));
	if (!tmp)
		return (NULL);
	while (str[index_sep + i])
	{
		tmp[i] = str[index_sep + i];
		i++;
	}
	tmp[i] = '\0';
	res = ft_strtrim(tmp, " ");
	return (free(tmp), res);
}

char *get_identifier(char **file, char *identifier)
{
	int		i;
	char	*res;
	
	i = 0;
	while (file[i] && ft_strncmp(file[i], identifier, ft_strlen(identifier)))
		i++;
	res = ft_strtokstr(file[i], identifier);
	return (res);
}

int get_pos(char **map, char pos)
{
	int	i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (pos == 'x')
					return (j);
				else if (pos == 'y')
					return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
