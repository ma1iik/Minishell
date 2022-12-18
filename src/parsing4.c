/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3 copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:45:05 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 10:08:21 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_one_group_function(t_data *data, int grp_nb, int ii)
{
	int		i;
	int		j;
	int		start;

	i = ii;
	j = 0;
	while (ft_isspace(data->cmd[i]))
		i++;
	start = i;
	while (data->cmd[i])
	{
		i++;
		j++;
	}
	data->cmd_tab[grp_nb] = ft_calloc(j + 1, sizeof(char));
	ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
	return (0);
}
