/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:45:05 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/21 22:36:36 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sg_quotes(t_data *data, int *i, int *j, char *c_char)
{
	*c_char = data->cmd[*i];
	*i += 1;
	while (data->cmd[*i] && (data->cmd[*i] != *c_char))
	{
		*i += 1;
		*j += 1;
	}
	*i += 1;
	*j += 2;
}

void	sg_noquotes(t_data *data, int *i, int *j)
{
	while (data->cmd[*i] && data->cmd[*i] != '|'
		&& data->cmd[*i] != '"' && data->cmd[*i] != '\'' )
	{
		*i += 1;
		*j += 1;
	}
}

int	sg_one(t_data *data, int grp_nb, int i)
{
	if (grp_nb == data->groups)
		return (1);
	if (data->groups == 1 || grp_nb + 1 == data->groups)
	{
		ft_one_group_function(data, grp_nb, i);
		return (1);
	}
	return (0);
}

void	ft_save_groups(t_data *d, int grp_nb, int ii, int start)
{
	int		i;
	int		j;
	char	c_char;

	i = ii;
	j = 0;
	start = i;
	if (sg_one(d, grp_nb, i))
		return ;
	while (d->cmd[i] && grp_nb < d->groups)
	{
		if (d->cmd[i] && d->cmd[i] == '|')
		{
			sg_cmdtab(d, grp_nb, j, start);
			sg_savetab(d, &i, grp_nb);
			return ;
		}
		else if (d->cmd[i] && (d->cmd[i] == '"' || d->cmd[i] == '\''))
			sg_quotes(d, &i, &j, &c_char);
		else if (d->cmd[i] && d->cmd[i] != '|' && d->cmd[i] != '"'
			&& d->cmd[i] != '\'' )
			sg_noquotes(d, &i, &j);
	}
}

int	ft_custom_split(t_data *data)
{
	data->groups = 0;
	if (!ft_logic_groups(data, ft_strlen_rl(data->cmd), 0))
		return (0);
	if (!ft_inv_char(data->cmd))
		return (0);
	data->cmd_tab = ft_calloc(data->groups + 1, sizeof(char *));
	ft_save_groups(data, 0, 0, 0);
	return (1);
}
