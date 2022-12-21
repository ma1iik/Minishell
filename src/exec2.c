/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/21 20:17:48 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execcmd(t_data *data, char **env)
{
	int	execc;

	if (ft_isbuiltin(data))
	{
		ft_exbuiltin(data);
		exit (0);
	}
	else
	{
		execc = execve(data->cmd_l->cmd[0], data->cmd_l->cmd, env);
		if (execc == -1)
		{
			ft_exec_err(data, errno, env);
		}
	}
}

int	ft_check_redir(t_data *data, int i)
{
	if (data->cmd_l->redir[0] != NULL)
	{
		i = 3;
		if (data->cmd_l->redir[1] == NULL)
		{
			printf("syntax error near unexpected token `newline\'\n");
			g_glv.redsig = 0;
			return (0);
		}
		else if (data->cmd_l->redir[2] != NULL)
		{
			while (i <= ft_tab_len(data->cmd_l->redir))
			{
				if (data->cmd_l->redir[i] == NULL)
				{
					printf("syntax error near unexpected token `newline\'\n");
					g_glv.redsig = 0;
					return (0);
				}
				i += 2;
			}
		}
	}
	return (1);
}
