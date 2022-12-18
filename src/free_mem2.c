/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:03:19 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:53 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_cmdl(t_data *data)
{
	t_cmdl	*tmp;
	int		i;

	i = 0;
	tmp = data->cmd_l_free;
	while (data->cmd_l_free)
	{
		tmp = data->cmd_l_free;
		data->cmd_l_free = data->cmd_l_free->next;
		while (i < tmp->nb_args)
		{
			free(tmp->cmd[i]);
			i++;
		}
		i = 0;
		while (tmp->redir[i])
		{
			free(tmp->redir[i]);
			i++;
		}
		free (tmp->cmd);
		free (tmp->redir);
		free(tmp);
		}
}

void	ft_free_envstr(t_data *data)
{
	int		i;

	i = 0;
	if (!data->env_str)
		return ;
	while (data->env_str[i])
	{
		free(data->env_str[i]);
		i++;
	}
	free (data->env_str);
}
