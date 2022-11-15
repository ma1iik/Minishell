/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:06:24 by ma1iik            #+#    #+#             */
/*   Updated: 2022/11/15 06:05:53 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exst(int num)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "?") == 0)
		{
			tmp.value = ft_strdup(ft_itoa(num));
			return ;
		}
		tmp = tmp->next
	}
	retun ;
}
