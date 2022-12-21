/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:25:29 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 12:13:14 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_tok(t_data *data, int type, char *value)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = ft_calloc(sizeof(t_token), data->tok_nb + 1);
	if (!tmp)
		return ;
	while (i < data->tok_nb)
	{
		tmp[i].e_type = data->tokens[i].e_type;
		tmp[i].value = ft_strdup(data->tokens[i].value);
		i++;
	}
	tmp[i].e_type = type;
	tmp[i].value = ft_strdup(value);
	if (data->tokens)
		ft_free_tokens(data);
	data->tokens = tmp;
	data->tok_nb++;
}

int	ft_token_filename(t_data *data, int i)
{
	char	*file;
	int		start;
	int		end;

	while (ft_isspace(data->lexer.c))
		skip_space(data);
	if (data->lexer.c == '\0' || data->lexer.c == '|')
		return (0);
	start = data->lexer.i;
	while (data->lexer.c && !ft_isspace(data->lexer.c)
		&& data->lexer.c != '<' && data->lexer.c != '>')
		lexer_advance(data);
	end = data->lexer.i;
	file = ft_calloc(sizeof(char), (end - start + 1));
	while (start < end)
	{
		file[i] = data->lexer.content[start];
		i++;
		start++;
	}
	file[i] = '\0';
	ft_init_tok(data, FILE_NAME, file);
	free (file);
	return (1);
}

int	ft_quote(t_data *data)
{
	if (data->lexer.c == '\'' || data->lexer.c == '"')
	{
		if (data->lexer.c == '\'')
			return (1);
		if (data->lexer.c == '"')
			return (2);
	}
	return (0);
}

void	ft_cmdtok2(t_data *data)
{
	if (ft_separated(data))
		return ;
	else
		ft_cmdtok(data, 0, 0);
}

void	ft_cmdtok(t_data *data, int qt, int cp)
{
	while (data->lexer.c != '\0')
	{
		while (!qt && !ft_separated(data))
		{
			qt = ft_quote(data);
			if (!qt)
				lexer_advance(data);
		}
		if (ft_separated(data))
			return ;
		else if (qt)
		{
			lexer_advance(data);
			cp = ft_quote(data);
			while (cp != qt)
			{
				cp = ft_quote(data);
				lexer_advance(data);
			}
			qt = 0;
		}
		ft_cmdtok2(data);
	}
}
