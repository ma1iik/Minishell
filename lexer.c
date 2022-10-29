/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:57:26 by ma1iik            #+#    #+#             */
/*   Updated: 2022/10/29 08:46:44 by ma1iik           ###   ########.fr       */
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
	while (ft_isspace(data->lexer.c))
		{
			data->lexer.i++;
			data->lexer.c = data->lexer.content[data->lexer.i];
		}
}

t_token   *get_next_token(t_data *data)
{
	int		cmd;

	cmd = 0;
	while (data->lexer.c != '\0' && data->lexer.i < ft_strlen(data->lexer.content))
	{
		if (data->lexer.c == ' ')
			lexer_skip_whitespace(data);
		if (data->lexer.c == '<')
			ft_token_l_red(data);
		else if (data->lexer.c == '>')
			ft_token_r_red(data);
		else
			cmd = ft_tokenise_rest(data, cmd);
	}
}

t_token *collect_opened_str(t_data *data)
{
	
}

char *get_char_as_str(t_data *data)
{
	
}

