/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:02:31 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 17:12:13 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_2env(char *cmd, int i)
{
	t_list	*tmp;
	char	**str;

	str = ft_split(cmd, '=');
	if (i == 1)
		tmp = g_glv.env_exp;
	else
		tmp = g_glv.env;
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
		{
			printf("found exp\n");
			free(tmp->value);
			if (str[1] != NULL)
				tmp->value = ft_strdup(str[1]);
			else
				tmp->value = NULL;
			tmp->flag = 0;
		}
		tmp = tmp->link;
	}
	ft_free_2d(str);
}

t_list	*ft_lstnew_exp(char *name, char *val, int num)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list), 1);
	if (!name)
		return (NULL);
	if (!new)
		return (NULL);
	if (num == 1)
	{
		new->name = ft_strdup(name);
		new->value = NULL;
		new->flag = 1;
	}
	else if (num == 0)
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(val);
	}
		new->link = NULL;
	return (new);
}

void	ft_exec_export(char *cmd, int num)
{
	char	**cmd_sp;

	cmd_sp = ft_split(cmd, '=');
	if (num == 2)
	{
		ft_lstadd_back(&g_glv.env, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 0));
		ft_lstadd_back(&g_glv.env_exp, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 0));
	}
	else if (num == 3)
	{
		ft_lstadd_back(&g_glv.env_exp, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 1));
	}
	g_glv.env_sig = 1;
	ft_free_2d(cmd_sp);
}

void	exec_export(char **cmd, int c)
{
	if (ft_check_ravno(cmd[c]) && ft_exp_exist(cmd[c]))
	{
		ft_unset_2env(cmd[c], 1);
		ft_unset_2env(cmd[c], 2);
	}
	else if (ft_check_ravno(cmd[c]) && !ft_exp_exist(cmd[c]))
		ft_exec_export(cmd[c], 2);
	else if (!ft_check_ravno(cmd[c]) && !ft_exp_exist(cmd[c]))
		ft_exec_export(cmd[c], 3);
}

void	ft_export(t_data *data, char **cmd, int c)
{
	int		i;

	i = 0;
	if (ft_tab_len(cmd) == 1)
		ft_print_exp();
	else
	{
		while (cmd[c] && cmd[c] != NULL)
		{
			if (ft_exp_err(cmd[c]))
			{
				exec_export(cmd, c);
			}
			else
				i = 1;
			c++;
		}
	}
	if (i == 0)
		ft_exst(0);
	if (data->groups != 1 && i == 1)
		exit(1);
}
