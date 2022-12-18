/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:53 by misrailo         ###   ########.fr       */
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

int	get_next_token(t_data *data)
{
	int		cmd;
	char	*tok;
	int		len;

	cmd = 0;
	len = ft_strlen(data->lexer.content);
	while (data->lexer.c != '\0' && data->lexer.i < len)
	{
		skip_space(data);
		if (data->lexer.c == '<')
		{
			if (!ft_token_l_red(data))
				return (0);
		}
		else if (data->lexer.c == '>')
		{
			if (!ft_token_r_red(data))
				return (0);
		}
		else if (data->lexer.c == '|')
		{
			ft_init_tok(data, PIPE, "|");
			lexer_advance(data);
			cmd = 0;
		}
		else if (cmd == 0)
		{
			printf("cmd tok\n");
			tok = ft_take_cmd(data);
			ft_init_tok(data, CMD, tok);
			free (tok);
			cmd = 1;
		}
		else if (!ft_separated(data) && cmd != 0)
		{
			printf("arg tok\n");
			tok = ft_take_cmd(data);
			ft_init_tok(data, ARG, tok);
			free (tok);
		}
	}
	ft_init_tok(data, END, "\0");
	return (1);
}
