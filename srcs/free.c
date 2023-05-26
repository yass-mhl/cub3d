/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:46:27 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/26 05:48:45 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_free_all_tab(char **tab, int nb)
{
	int	i;

	(void)nb;
	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
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
	free(config);
}
void free_data(t_map *data)
{
	if (data->file)
		ft_free_all_tab(data->file, 0);
	if (data->map)
		ft_free_all_tab(data->map, 0);
}
