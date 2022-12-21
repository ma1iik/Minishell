/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:34 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:37 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_n(char **cmd)
{
	int	i;
	int	j;

	if (ft_strncmp(cmd[1], "-n", 2) != 0)
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			j = 2;
			while (cmd[i][j])
			{
				if (cmd[i][j] == 'n')
					j++;
				else
					return (i);
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}

void	ft_echo_no_n(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("\n");
}

void	ft_echo_non(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("\n");
}

void	ft_echo(t_data *data, char **cmd)
{
	int	i;

	(void)data;
	if (cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = ft_check_n(cmd);
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && i > 1)
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
	}
	else
		ft_echo_non(cmd);
	ft_exst(0);
}
