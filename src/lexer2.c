/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 07:13:09 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_lexer(t_data *data)
{
	data->d_i = 0;
	data->lexer.i = 0;
	data->tok_nb = 0;
}

int	lexer_advance(t_data *data)
{
	int		len;

	len = ft_strlen(data->lexer.content);
	if (data->lexer.c != '\0' && data->lexer.i < len)
	{
		data->lexer.i++;
		data->lexer.c = data->lexer.content[data->lexer.i];
		return (1);
	}
	return (0);
}

void	skip_space(t_data *data)
{
	if (ft_isspace(data->lexer.c))
	{
		while (ft_isspace(data->lexer.c))
		{
			data->lexer.i++;
			data->lexer.c = data->lexer.content[data->lexer.i];
		}
	}
}

void	init_pipe(t_data *data, int *cmd)
{
	ft_init_tok(data, PIPE, "|");
	lexer_advance(data);
	*cmd = 0;
}

void	init_cmd(t_data *data, int *cmd, char **tok)
{
	*tok = ft_take_cmd(data);
	ft_init_tok(data, CMD, *tok);
	free (*tok);
	*cmd = 1;
}
