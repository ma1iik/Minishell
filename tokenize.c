/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:25:29 by ma1iik            #+#    #+#             */
/*   Updated: 2022/10/31 13:26:09 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_token_l_red(t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1 == '<'])
	{
		ft_init_tok(data, DL_RED, "<<");
		lexer_advance(data);
	}
	else
		ft_init_tok(data, L_RED, "<");
	lexer_advance(data);
	ft_token_filename(data);
}

void	ft_token_r_red (t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1 == '>'])
	{
		ft_init_tok(data, DL_RED, ">>");
		lexer_advance(data);
	}
	else
		ft_init_tok(data, L_RED, ">");
	lexer_advance(data);
	ft_token_filename(data);
	
}

void	ft_token_filename(t_data *data)
{
	char	*file;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (ft_isspace(data->lexer.c))
		skip_space(data);
	start = data->lexer.i;
	while (!ft_isspace(data->lexer.c) && data->lexer.c != '<' && data->lexer.c != '>')
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
}

char	*ft_take_cmd(t_data *data)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = data->lexer.i;
	while (!ft_separated(data))
		lexer_advance(data);
	end = data->lexer.i;
	str = ft_calloc(sizeof(char), (end - start + 1));
	while (start < end)
	{
		str[i] = data->lexer.content[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);	
}

char	*ft_take_arg(t_data *data)
{
	char	*str;
	int		start;
	int		end;
	int		i;
	char	sign;

	i = 0;
	start = data->lexer.i;
	while (!ft_separated(data))
	{
		if (data->lexer.c == '\'' || data->lexer.c == '"')
		{
			sign = data->lexer.c;
			lexer_advance(data);
			while (data->lexer.c != sign)
				lexer_advance(data);
			lexer_advance(data);
		}
		lexer_advance(data);
	}
	end = data->lexer.i;
	str = ft_calloc(sizeof(char), (end - start + 1));
	while (start < end)
	{
		str[i] = data->lexer.content[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);	
}

void	ft_rm_quotes(t_data *data)
{
	int		j;
	int		i;
	char	sign;
	int		start;
	int		end;

	i = 0;
	while (i < data->tok_nb)
	{
		j = 0;
		while (data->tokens[i].value[j])
		{
			if (data->tokens[i].value[j] == '\'' || data->tokens[i].value[j] == '"')
			{
				start = j;
				sign = data->tokens[i].value[j];
				j++;
				while (data->tokens[i].value[j] != sign && data->tokens[i].value[j])
					j++;
				end = j;
				data->tokens[i].value = ft_rm_quotes2(data->tokens[i].value, start, end);
				j = j - 2;
			}
			j++;
		}
		i++;
	}
}

char *ft_rm_quotes2(char *str, int start, int end)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(str) - 2);
	while (str[i])
	{
		if (i != start && i != end)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[i] = '\0';
	free (str);
	return (tmp);
}