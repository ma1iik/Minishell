/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmdl2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:58:09 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:22:38 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_redir(t_data *d, int i, int arg)
{
	char	**redirs;
	int		red_c;
	int		p;

	p = d->cmdl_i;
	red_c = ft_count_red(d, d->cmdl_i) + 1;
	redirs = ft_calloc(sizeof(char *), red_c);
	while (d->tokens[p].e_type && d->tokens[p].e_type != PIPE
		&& d->tokens[p].e_type != END && i < red_c)
	{
		if (!arg && (d->tokens[p].e_type < 5
				|| d->tokens[p].e_type == 6))
		{
			redirs[i] = ft_strdup(d->tokens[p].value);
			i++;
			arg = 1;
		}
		else if ((arg && (d->tokens[p].e_type < 5
					|| d->tokens[p].e_type == 6 || d->tokens[p].e_type == 8)))
			redirs[i++] = ft_strdup(d->tokens[p].value);
		p++;
	}
	redirs[i] = NULL;
	return (redirs);
}

t_cmdl	*ft_cmdl_new(t_data *data)
{
	t_cmdl	*tmp;
	int		x;

	x = data->cmdl_i;
	tmp = ft_calloc(sizeof(t_cmdl), 1);
	tmp->nocmd = 1;
	tmp->redir = ft_get_redir(data, 0, 0);
	tmp->cmd = ft_get_args(data, tmp, 0, 0);
	tmp->nb_args = ft_count_arg(data, x);
	tmp->in = STDIN_FILENO;
	tmp->out = STDOUT_FILENO;
	tmp->exit = 0;
	return (tmp);
}

void	ft_set_cmdl(t_data *data)
{
	ft_addback_cmdl(&data->cmd_l, ft_cmdl_new(data));
}

void	ft_fill_cmdl(t_data *data)
{
	data->cmdl_i = 0;
	while (data->cmdl_i < data->tok_nb
		&& data->tokens[data->cmdl_i].e_type != END)
	{
		if (data->tokens[data->cmdl_i].e_type == PIPE)
			data->cmdl_i++;
		else if (!data->tokens)
			return ;
		else
			ft_set_cmdl(data);
	}
}
