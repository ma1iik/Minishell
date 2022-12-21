/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 07:13:21 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_toks(t_data *data)
{
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
	return (1);
}

int	get_next_token(t_data *data, int len)
{
	int		cmd;
	char	*tok;

	cmd = 0;
	len = ft_strlen(data->lexer.content);
	while (data->lexer.c != '\0' && data->lexer.i < len)
	{
		skip_space(data);
		if (!redir_toks(data))
			return (0);
		else if (data->lexer.c == '|')
			init_pipe(data, &cmd);
		else if (cmd == 0)
			init_cmd(data, &cmd, &tok);
		else if (!ft_separated(data) && cmd != 0)
		{
			tok = ft_take_cmd(data);
			ft_init_tok(data, ARG, tok);
			free (tok);
		}
	}
	ft_init_tok(data, END, "\0");
	return (1);
}
