/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:03:19 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 22:59:48 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmdl(t_data *data)
{
	t_cmdl	*tmp;
	t_cmdl	*head;
	int		i;

	i = 0;
	tmp = data->cmd_l_free;
	head = data->cmd_l_free;
	while (head != NULL)
    {
		tmp = head;
		head = head->next;
		while (tmp->cmd[i])
		{
			free(tmp->cmd[i]);
			i++;
		}
		free (tmp->cmd);
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