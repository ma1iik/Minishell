/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:59:27 by ma1iik            #+#    #+#             */
/*   Updated: 2022/11/26 22:32:29 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_rules(t_data *data, int i)
{
	if (data->tokens[i].e_type < 6 && (data->tokens[i + 1].e_type == PIPE ||
		data->tokens[i + 1].e_type == END))
		return (0);
	return (1);
}

int	ft_check_rules(t_data *data)
{
	int		i;
	
	i = 0;
	while (i < data->tok_nb)
	{
		if (!ft_redir_rules(data, i))
		{
			printf("Parse error near `%s'\n", data->tokens[i].value);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_rules(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->tok_nb)
	{
		if (!ft_check_rules(data))
			return (0);
		// tmp = tmp->link;
		i++;
	}
	return (1);
}
