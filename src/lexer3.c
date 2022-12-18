/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 12:00:46 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_l_red(t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1] == '<')
	{
		ft_init_tok(data, DL_RED, "<<");
		lexer_advance(data);
		lexer_advance(data);
		if (!ft_token_filename(data, 0))
			return (ft_filename_error(data));
	}
	else
	{
		ft_init_tok(data, L_RED, "<");
		lexer_advance(data);
		if (!ft_token_filename(data, 0))
			return (ft_filename_error(data));
	}
	return (1);
}

int	ft_token_r_red(t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1] == '>')
	{
		ft_init_tok(data, DL_RED, ">>");
		lexer_advance(data);
		lexer_advance(data);
		if (!ft_token_filename(data, 0))
			return (ft_filename_error(data));
	}
	else
	{
		ft_init_tok(data, L_RED, ">");
		lexer_advance(data);
		if (!ft_token_filename(data, 0))
			return (ft_filename_error(data));
	}
	return (1);
}

int	ft_filename_error(t_data *data)
{
	if (!data->lexer.content[data->lexer.i])
		printf("syntax error near `\\n'\n");
	else
		printf("syntax error near `%c'\n'", data->lexer.content[data->lexer.i]);
	return (0);
}
