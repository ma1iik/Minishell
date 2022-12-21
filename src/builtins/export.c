/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:50 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:54 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_2env(char *cmd)
{
	t_list	*tmp;
	char	**str;
	int		num;

	str = ft_split(cmd, '=');
	tmp = g_glv.env;
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
		{
			free(tmp->value);
			if (str[1] != NULL)
				tmp->value = ft_strdup(str[1]);
			else
				tmp->value = NULL;
			tmp->flag = 0;
			num = 1;
		}
		tmp = tmp->link;
	}
	if (num != 1)
		ft_lstadd_back(&g_glv.env, ft_lstnew_addenv(str[0], str[1]));
	ft_free_2d(str);
}

t_list	*ft_lstnew_addenv(char *name, char *val)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (val && val != NULL)
		new->name = ft_strdup(val);
	else
		new->value = NULL;
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
		ft_unset_2envexp(cmd[c]);
		ft_unset_2env(cmd[c]);
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
