/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:10:53 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/10 14:34:37 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_uns_err(char *str)
{
	if (!ft_isalpha(str[0]))
	{
		printf("unset: %s: invalid parameter name\n", str);
		ft_exst(1);
		return (0);
	}
	return (1);
}

void	ft_pos_zero(t_list **cur, int num)
{
	if (num == 1)
		glv.env = glv.env->link;
	else if (num == 2)
		glv.env_exp = glv.env_exp->link;
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

void	ft_unset_var_exp(char **cmd, int i, int pos)
{
	t_list	*prev;
	t_list	*cur;

	cur = glv.env_exp;
	prev = glv.env_exp;
	if (!glv.env_exp)
		return ;
	while (cur)
	{
		if (ft_strcmp(cur->name, cmd[i]) == 0)
		{
			if (pos == 0)
				ft_pos_zero(&cur, 2);
			else
				ft_pos_nonzero(&cur, &prev);
		}
		prev = cur;
		cur = cur->link;
	}
	return ;
}

void	ft_unset_var(char **cmd, int i, int pos)
{
	t_list	*prev;
	t_list	*cur;

	cur = glv.env;
	prev = glv.env;
	if (!glv.env)
		return ;
	while (cur)
	{
		if (ft_strcmp(cur->name, cmd[i]) == 0)
		{
			if (pos == 0)
				ft_pos_zero(&cur, 1);
			else
				ft_pos_nonzero(&cur, &prev);
		}
		prev = cur;
		cur = cur->link;
	}
	ft_unset_var_exp(cmd, i, 0);
	glv.env_sig = 1;
	return ;
}

void	ft_unset(char **cmd)
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
				ft_unset_var(cmd, i, 0);
			else
				er = 1;
			i++;
		}
	}
	ft_exst(er);
}