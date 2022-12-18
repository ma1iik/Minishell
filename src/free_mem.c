/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 05:45:22 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:25:17 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dealloc_envstr(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_str[i])
	{
		free (data->env_str[i]);
		i++;
	}
	free (data->env_str);
}

void	ft_dealloc_tok(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->tok_nb)
	{
		free(data->tokens[i].value);
		i++;
	}
}

void	ft_dealloc_lexer(t_data *data)
{
	free (data->lexer.content);
	free (&data->lexer);
}

void	ft_dealloc_cmds(t_data *data)
{
	ft_free_2d(data->cmd_tab);
}

void	ft_free_cml1(t_data *data)
{
	int		i;

	i = 0;
	while (data->cmd_l->cmd[i])
	{
		free(data->cmd_l->cmd[i]);
		i++;
	}
	i = 0;
	while (data->cmd_l->redir[i])
	{
		free(data->cmd_l->redir[i]);
		i++;
	}
	free(data->cmd_l->cmd);
	free(data->cmd_l->redir);
	free(data->cmd_l);
	data->cmd_l = NULL;
}
