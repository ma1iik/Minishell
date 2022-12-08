/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:56:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 10:39:56 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_exit(char **cmd)
{
	if (cmd[1] == NULL || (ft_numonly(cmd[1]) && !cmd[2]))
	{
		printf("exit\n");
		exit(0);
	}
	else if (ft_numonly(cmd[1]) && cmd[2])
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		ft_exst(0);
	}
	else if (!ft_numonly(cmd[1]))
	{
		printf("exit\n");
		printf("exit: ");
		printf("%s", cmd[1]);
		printf(": numeric argument required\n");
		exit(0);
	}
}