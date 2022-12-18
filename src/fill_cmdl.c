/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:58:09 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:21:46 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(t_data *data, int x)
{
	int		cnt;
	int		arg;

	cnt = 0;
	arg = 0;
	while (data->tokens[x].e_type && data->tokens[x].e_type != PIPE
		&& data->tokens[x].e_type != END)
	{
		if (data->tokens[x].e_type < 5 || data->tokens[x].e_type == 6)
			arg = 1;
		else if (!arg && (data->tokens[x].e_type == ARG
				|| data->tokens[x].e_type == CMD))
		{
			cnt++;
		}
		x++;
	}
	return (cnt);
}

char	**ft_get_args(t_data *data, t_cmdl *tmp, int arg_c, int i)
{
	char	**args;
	int		arg;

	arg = 0;
	arg_c = ft_count_arg(data, data->cmdl_i) + 1;
	args = ft_calloc(sizeof(char *), arg_c);
	while (data->tokens[data->cmdl_i].e_type
		&& data->tokens[data->cmdl_i].e_type != PIPE
		&& data->tokens[data->cmdl_i].e_type != END && i < arg_c)
	{
		if (!arg && (data->tokens[data->cmdl_i].e_type == CMD
				|| data->tokens[data->cmdl_i].e_type == ARG))
		{
			if (data->tokens[data->cmdl_i].e_type == CMD)
				tmp->nocmd = 0;
			args[i++] = ft_strdup(data->tokens[data->cmdl_i].value);
		}
		else if (data->tokens[data->cmdl_i].e_type < 5
			|| data->tokens[data->cmdl_i].e_type == 6)
			arg = 1;
		data->cmdl_i++;
	}
	args[i] = NULL;
	return (args);
}

t_cmdl	*ft_lst_cmdl(t_cmdl *cmdl)
{
	if (!cmdl)
		return (NULL);
	while (cmdl->next)
		cmdl = cmdl->next;
	return (cmdl);
}

void	ft_addback_cmdl(t_cmdl **cmd, t_cmdl *new)
{
	t_cmdl	*lst;

	if (!*cmd)
	{
		new->pos = 1;
		*cmd = new;
		return ;
	}
	lst = ft_lst_cmdl(*cmd);
	new->pos = lst->pos + 1;
	if (new->pos != 1)
		new->prev = lst;
	else
		new->prev = NULL;
	lst->next = new;
}

int	ft_count_red(t_data *data, int x)
{
	int		cnt;
	int		arg;

	cnt = 0;
	arg = 0;
	while (data->tokens[x].e_type
		&& data->tokens[x].e_type != PIPE && data->tokens[x].e_type != END)
	{
		if (!arg && (data->tokens[x].e_type < 5 || data->tokens[x].e_type == 6))
		{
			arg = 1;
			cnt++;
		}
		else if (arg && (data->tokens[x].e_type < 5
				|| data->tokens[x].e_type == 6 || data->tokens[x].e_type == 8))
			cnt++;
		x++;
	}
	return (cnt);
}
