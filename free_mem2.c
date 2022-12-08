/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:03:19 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 11:11:51 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmdl(t_data *data)
{
	t_cmdl	*tmp;
	t_cmdl	*head;

	tmp = data->cmd_l;
	head = data->cmd_l;
	while (head != NULL)
    {
		tmp = head;
		head = head->next;
		ft_free_2d(tmp->cmd);
		free(tmp);
    }
}