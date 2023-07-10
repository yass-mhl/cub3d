/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:46:27 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/03 19:59:20 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_all_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_all_tab_int(int **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_textures(int **textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i])
			free(textures[i]);
		i++;
	}
	if (textures)
		free(textures);
}

void	free_config(t_config *config)
{
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	if (config->f)
		free(config->f);
	if (config->c)
		free(config->c);
	if (config->mlx)
		free(config->mlx);
	if (config->textures)
		free_textures(config->textures);
	if (config->pixelMap)
		ft_free_all_tab_int(config->pixelMap);
	free(config);
}

void	free_data(t_map *data)
{
	if (data->file)
		ft_free_all_tab(data->file);
	if (data->map)
		ft_free_all_tab(data->map);
	free(data);
}
