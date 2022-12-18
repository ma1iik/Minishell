/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:25:29 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:53 by misrailo         ###   ########.fr       */
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

int	ft_token_filename(t_data *data)
{
	char	*file;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (ft_isspace(data->lexer.c))
		skip_space(data);
	if (data->lexer.c == '\0' || data->lexer.c == '|')
		return (0);
	start = data->lexer.i;
	while (data->lexer.c && !ft_isspace(data->lexer.c) && data->lexer.c != '<' && data->lexer.c != '>')
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

int		ft_quote(t_data *data)
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

void		ft_cmdtok(t_data *data)
{
	int		qt;
	int		cp;
	
	qt = 0;
	cp = 0;
	while (data->lexer.c != '\0')
	{
		while(!qt && !ft_separated(data))
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
		if (ft_separated(data))
			return ;
		else
			ft_cmdtok(data);
	}
}

char	*ft_take_cmd(t_data *data)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = data->lexer.i;
	ft_cmdtok(data);
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
				printf("start is %d\n", start);
				sign = data->tokens[i].value[j];
				j++;
				while (data->tokens[i].value[j] != sign && data->tokens[i].value[j])
					j++;
				end = j;
				printf("end is %d\n", end);
				data->tokens[i].value = ft_rm_quotes2(data->tokens[i].value, start, end);
				printf("token val wo quotes is --> %s\n\n\n\n", data->tokens[i].value);
				j = j - 2;
			}
			j++;
		}
		i++;
	}
}

char	*ft_rm_quotes2(char *str, int start, int end)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(str));
	while (str[i])
	{
		if (i != start && i != end)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	free (str);
	return (tmp);
}
