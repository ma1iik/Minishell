/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:59:27 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 10:00:11 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redir_rules(t_data *data, int i)
{
	if (data->tokens[i].e_type < 6 && (data->tokens[i + 1].e_type == PIPE
			|| data->tokens[i + 1].e_type == END))
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
			printf("syntax error near `%s'\n", data->tokens[i].value);
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
		i++;
	}
	return (1);
}

void	sg_cmdtab(t_data *data, int grp_nb, int j, int start)
{
	data->cmd_tab[grp_nb] = ft_calloc(j + 1, sizeof(char));
	ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
}

void	sg_savetab(t_data *data, int *i, int grp_nb)
{
	*i += 1;
	ft_save_groups(data, grp_nb, *i, 0);
}
