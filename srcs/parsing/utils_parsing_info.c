/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:44:40 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/20 14:37:00 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	is_less_255(char *str)
{
	int	i;

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

int	check_commas(char *str)
{
	int	i;
	int	commas;

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

int	check_elements(char **elements)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (elements[i])
	{
		trimmed = ft_strtrim(elements[i], " ");
		if (!is_less_255(trimmed))
		{
			free(trimmed);
			return (false);
		}
		free(trimmed);
		i++;
	}
	return (true);
}

int	check_f_c(t_config *config)
{
	char	**f;
	char	**c;

	f = ft_split(config->f, ',');
	c = ft_split(config->c, ',');
	if (ft_tablen(f) != 3 || ft_tablen(c) != 3)
	{
		return (ft_free_all_tab(c), ft_free_all_tab(f), false);
	}
	if (!check_elements(f) || !check_elements(c))
		return (ft_free_all_tab(c), ft_free_all_tab(f), false);
	return (ft_free_all_tab(c), ft_free_all_tab(f), true);
}
