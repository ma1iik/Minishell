/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:03:11 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/17 00:21:36 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	t_list	*tmp;

	tmp = g_glv.env;
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(tmp->name, "?") != 0)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->link;
	}
	ft_exst(0);
}
