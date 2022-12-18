/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:45:05 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 10:08:34 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_if_closed(char c_char, int ii, t_data *data)
{
	char	c;
	int		i;

	c = c_char;
	if ((data->cmd[ii + 1]) == '\0')
	{
		return (-1);
	}
	else
		i = ii + 1;
	while (data->cmd[i] && data->cmd[i] != c)
		i++;
	if (data->cmd[i] == c)
	{
		return (i);
	}
	else
	{
		return (-1);
	}
}

int	double_pipe(t_data *data, int *i, int *pipes)
{
	while (ft_isspace(data->cmd[*i + 1]))
		*i += 1;
	if (data->cmd[*i + 1] == '|')
	{
		printf("syntax error near `|'\n");
		return (0);
	}
	*pipes += 1;
	*i += 1;
	return (1);
}

int	lg_ret(t_data *data, int pipes)
{
	if (pipes + 1 == data->groups)
		return (1);
	else if (pipes == 0 && data->groups == 0)
		return (0);
	printf("Error: wrong pipe usage\n");
	return (0);
}

int	lg_quotes(t_data *data, int *i)
{
	if (data->cmd[*i] == '"' || data->cmd[*i] == '\'')
	{
		*i = ft_check_if_closed(data->cmd[*i], *i, data);
		if (*i == -1)
		{
			printf("Error: unclosed quotes\n");
			return (0);
		}
	}
	*i += 1;
	return (1);
}

int	ft_logic_groups(t_data *data, int end, int pipes)
{
	int		i;

	i = 0;
	while (i < end)
	{
		if (data->cmd[i] != '|')
		{
			while (data->cmd[i] != '|' && data->cmd[i] != '\0')
			{
				if (!lg_quotes(data, &i))
					return (0);
			}
			data->groups += 1;
		}
		if (data->cmd[i] == '|')
		{
			if (!double_pipe(data, &i, &pipes))
				return (0);
		}
	}
	return (lg_ret(data, pipes));
}
