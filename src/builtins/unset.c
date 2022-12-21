/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:02:45 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:02:47 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pos_zero(t_list **cur, int num)
{
	if (num == 1)
		g_glv.env = g_glv.env->link;
	else if (num == 2)
		g_glv.env_exp = g_glv.env_exp->link;
	free((*cur)->name);
	free((*cur)->value);
	free(*cur);
	return ;
}

void	ft_pos_nonzero(t_list **cur, t_list **prev)
{
	(*prev)->link = (*cur)->link;
	free((*cur)->name);
	free((*cur)->value);
	free(*cur);
	return ;
}

void	ft_unset_var_exp(char **cmd, int i)
{
	t_list	*prev;
	t_list	*cur;

	cur = g_glv.env_exp;
	prev = g_glv.env_exp;
	if (!g_glv.env_exp)
		return ;
	while (cur)
	{
		if (ft_strcmp(cur->name, cmd[i]) == 0)
		{
			if (cur == g_glv.env)
				ft_pos_zero(&cur, 2);
			else
				ft_pos_nonzero(&cur, &prev);
			return ;
		}
		prev = cur;
		cur = cur->link;
	}
	return ;
}

void	ft_unset_var(char **cmd, int i)
{
	t_list	*prev;
	t_list	*cur;

	cur = g_glv.env;
	prev = g_glv.env;
	if (!g_glv.env)
		return ;
	while (cur)
	{
		if (ft_strcmp(cur->name, cmd[i]) == 0)
		{
			if (cur == g_glv.env)
				ft_pos_zero(&cur, 1);
			else
				ft_pos_nonzero(&cur, &prev);
			break ;
		}
		prev = cur;
		cur = cur->link;
	}
	ft_unset_var_exp(cmd, i);
	g_glv.env_sig = 1;
	return ;
}

void	ft_unset(t_data *data, char **cmd)
{
	int		i;
	int		er;

	i = 1;
	er = 0;
	if (ft_tab_len(cmd) == 1)
	{
		printf("unset: not enough arguments\n");
		er = 1;
	}
	else
	{
		while (cmd[i])
		{
			if (ft_uns_err(cmd[i]))
				ft_unset_var(cmd, i);
			else
				er = 1;
			i++;
		}
	}
	ft_exst(er);
	if (er == 1 && data->groups != 1)
		exit(1);
}
