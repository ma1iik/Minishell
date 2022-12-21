/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:40 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:42 by tidigov          ###   ########.fr       */
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
		{
			if (tmp->value != NULL)
				printf("%s=%s\n", tmp->name, tmp->value);
			else
				printf("%s=\n", tmp->name);
		}
		tmp = tmp->link;
	}
	ft_exst(0);
}
