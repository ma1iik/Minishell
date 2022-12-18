/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:03:11 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:37 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_data *data, char **cmd)
{
	t_list	*tmp;

	tmp = g_glv.env;
	if (cmd[1] && cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		ft_exst(127);
		if (data->groups != 1)
			exit(127);
	}
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(tmp->name, "?") != 0)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->link;
	}
	ft_exst(0);
}
