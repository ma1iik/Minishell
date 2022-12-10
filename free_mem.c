/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 05:45:22 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/10 23:13:28 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	ft_dealloc_lexer(t_data *data)
// {
// 		free (data->cmd)
		
// }

void ft_free_all(t_data *data)
{
	//ft_dealloc_lexer(data);
	//ft_dealloc_tok(data);
	//ft_free_2d(data->cmd_tab);
	//free (data->cmd);
	ft_free_cmdl(data);
	ft_dealloc_cmds(data);
	ft_free_tokens(data);
	//ft_dealloc_
}