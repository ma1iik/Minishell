/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:25:29 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 12:12:55 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_take_cmd(t_data *data)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = data->lexer.i;
	ft_cmdtok(data, 0, 0);
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

void	ft_rm_quotes(t_data *d, int i, int j)
{
	char	sign;
	int		st;
	int		end;

	i = 0;
	while (i < d->tok_nb)
	{
		j = 0;
		while (d->tokens[i].value[j])
		{
			if (d->tokens[i].value[j] == '\'' || d->tokens[i].value[j] == '"')
			{
				st = j;
				sign = d->tokens[i].value[j];
				j++;
				while (d->tokens[i].value[j] != sign && d->tokens[i].value[j])
					j++;
				end = j;
				d->tokens[i].value = ft_rm_quotes2(d->tokens[i].value, st, end);
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
