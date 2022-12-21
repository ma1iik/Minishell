/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:45 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:47 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exst_c(char *str)
{
	t_list	*tmp;

	tmp = g_glv.env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "?") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(str);
			return ;
		}
		tmp = tmp->link;
	}
	return ;
}

int	ft_numonly(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

void	exit_not_num(t_data *data, char **cmd)
{
	if (data->groups == 1)
	{
		ft_exst(2);
		printf("exit\n");
	}
	printf("exit: %s: numeric argument required\n", cmd[1]);
	if (data->groups == 1)
		exit(0);
	else
		exit (2);
}

void	exit_num(t_data *data, char **cmd)
{
	ft_exst_c(cmd[1]);
	if (data->groups == 1)
		printf("exit\n");
	if (data->groups == 1)
		exit(0);
	else
		exit(ft_atoi(cmd[1]));
}

void	ft_exit(t_data *data, char **cmd)
{
	if (cmd[1] == NULL)
	{
		if (data->groups == 1)
			printf("exit\n");
		exit(0);
	}
	else if ((ft_numonly(cmd[1]) && cmd[2] == NULL))
		exit_num(data, cmd);
	else if (ft_numonly(cmd[1]) && cmd[2])
	{
		if (data->groups == 1)
			printf("exit\n");
		printf("exit: too many arguments\n");
		ft_exst(1);
		if (data->groups != 1)
			exit(1);
	}
	else if (!ft_numonly(cmd[1]))
		exit_not_num(data, cmd);
}
