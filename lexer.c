/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/10/30 16:59:16 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_lexer(t_data *data)
{
	data->lexer.content = data->cmd;
	data->lexer.i = 0;
	data->tok_nb = 0;
	data->lexer.c = data->lexer.content[0];
}

int	lexer_advance(t_data *data)
{
	if (data->lexer.c != '\0' && data->lexer.i < ft_strlen(data->lexer.content))
	{
		data->lexer.i++;
		data->lexer.c = data->lexer.content[data->lexer.i];
		return(1);
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

t_token   *get_next_token(t_data *data)
{
	int		cmd;
	char	*tok;

	cmd = 0;
	while (data->lexer.c != '\0' && data->lexer.i < ft_strlen(data->lexer.content))
	{
		skip_space(data);
		if (data->lexer.c == '<')
			ft_token_l_red(data, cmd);
		else if (data->lexer.c == '>')
			ft_token_r_red(data, cmd);
		else if (cmd == 0)
		{
			tok = ft_take_cmd(data);
			ft_init_tok(data, CMD, tok);
			cmd = 1;
		}
		else if (data->lexer.c == '$' && cmd != 0)
		{
			tok = ft_take_arg(data);
			ft_init_tok(data, DOLLAR, tok);
		}
		else if (!ft_separated(data) && cmd != 0)
		{
			tok = ft_take_arg(data);
			ft_init_tok(data, ARG, tok);
		}
		free (tok);
	}
}

