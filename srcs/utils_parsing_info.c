/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:44:40 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/26 05:58:19 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int is_less_255(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_atoi(str) > 255 || ft_atoi(str) < 0)
		return (0);
	return (true);
}

// Peut etre mettre un ft_strtrim mais je suis pas sur, a voir

int check_f_c(t_config *config)
{
	char **f;
	char **c;
	int i;

	i = 0;
	f = ft_split(config->f, ',');
	c = ft_split(config->c, ',');
	if (ft_tablen(f) != 3 || ft_tablen(c) != 3)
		return (ft_free_all_tab(c, 0), ft_free_all_tab(f, 0), false);
	while (f[i] != NULL)
	{	
		if (!is_less_255(f[i]))
			return (ft_free_all_tab(c, 0), ft_free_all_tab(f, 0), false);
		i++;
	}
	i = 0;
	while (c[i])
	{
		if (!is_less_255(c[i]))
			return (ft_free_all_tab(f, 0), ft_free_all_tab(c, 0), false);
		i++;
	}
	return (ft_free_all_tab(c, 0), ft_free_all_tab(f, 0), true);
}

int check_commas(char *str)
{
	int i;
	int commas;
	
	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (0);
	return (1);
}


