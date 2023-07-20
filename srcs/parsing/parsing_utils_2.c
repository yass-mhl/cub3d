/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:15:58 by gansard           #+#    #+#             */
/*   Updated: 2023/07/20 15:35:47 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtokstr(char *str, char *sep)
{
	int		i;
	int		index_sep;
	char	*tmp;
	char	*res;

	i = 0;
	if (!str)
		return (NULL);
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

char	*get_identifier(char **file, char *identifier)
{
	int		i;
	char	*res;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (file[i] && ft_strncmp(file[i], identifier, ft_strlen(identifier)))
		i++;
	tmp = ft_strtokstr(file[i], identifier);
	tmp2 = ft_strtrim(tmp, " ");
	res = ft_strtrim(tmp2, "\n");
	return (free(tmp), free(tmp2), res);
}

int	check_path(char *path)
{
	if (!is_directory_is_valid(path))
		return (0);
	return (1);
}

int check_char_rgb(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	if (len > 3)
		return (0);
	return (1);
}

int	rgb_to_hex(char *rgb)
{
	int		r;
	int		g;
	int		b;
	int		hex_value;
	char	**tab;

	tab = ft_split(rgb, ',');
	if (!tab)
		return (-1);
	if (!tab[0] || !tab[1] || !tab[2])
		return (ft_free_all_tab(tab), -1);
	if (!check_char_rgb(tab[0]) || !check_char_rgb(tab[1])
			|| !check_char_rgb(tab[2]))
		return (ft_free_all_tab(tab), -1);
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	hex_value = (r << 16) | (g << 8) | b;
	return (ft_free_all_tab(tab), hex_value);
}
