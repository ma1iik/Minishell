/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:03:11 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/10 15:41:39 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	t_list	*tmp;

	tmp = glv.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?") == 0)
			tmp = tmp->link;
		else
		{
			printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->link;
		}
	}
}