/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:02:31 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 12:56:21 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_exp(void)
{
	t_list	*tmp;

	tmp = glv.env_exp;
	while (tmp)
	{
		if (ft_strcmp("?", tmp->name) == 0)
			tmp = tmp->link;
		else
		{
			if (tmp->value == NULL)
			{
				if (tmp->flag == 1)
					printf("declare -x %s\n", tmp->name);
				else
					printf("declare -x %s=\"\"\n", tmp->name);
			}
			else if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->link;
		}
	}	
}

int	ft_exp_err(char *str)
{
	if (!ft_isalpha(str[0]))
	{
		printf("export: `%s': not a valid identifier\n", str);
		ft_exst(1);
		return (0);
	}
	return (1);
}

int	ft_check_ravno(char	*str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getvarname(char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (s[len] != '=')
		len++;
	ret = ft_calloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int ft_exp_exist(char *s)
{
	char 	*name;
	t_list	*tmp;

	tmp = glv.env_exp;
	name = ft_getvarname(s);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(name);
			return (1);
		}
		tmp = tmp->link;
	}
	free(name);
	return (0);
}

void	ft_unset_2env(char **str)
{
	t_list	*tmp;

	tmp = glv.env;
	while (tmp)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(str[1]);
			tmp->flag = 0;
		}
		tmp = tmp->link;
	}
	tmp = glv.env_exp;
	while (tmp)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(str[1]);
			tmp->flag = 0;
		}
		tmp = tmp->link;
	}
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
		new->name = NULL;
		new->value =ft_strdup(val);
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
	if (num == 1)
	{
		ft_unset_2env(cmd_sp);
	}
	else if (num == 2)
	{
		ft_lstadd_back(&glv.env, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 0));
		ft_lstadd_back(&glv.env_exp, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 0));
	}
	else if (num == 3)
	{
		//ft_lstadd_back(&glv.env, ft_lstnew(cmd_sp[0]. cmd_sp[1], 1));
		ft_lstadd_back(&glv.env_exp, ft_lstnew_exp(cmd_sp[0], cmd_sp[1], 1));
	}
}

void	ft_export(char **cmd, int c)
{
	int		i;

	i = 0;
	if (ft_tab_len(cmd) == 1)
		ft_print_exp();
	else
	{
		while (cmd[c])
		{
			if(ft_exp_err(cmd[c]))
			{
				if (ft_check_ravno(cmd[c]) && ft_exp_exist(cmd[c]))
				{
					printf("LOL\n");
					ft_exec_export(cmd[c], 1);
				}
				else if (ft_check_ravno(cmd[c]) && !ft_exp_exist(cmd[c]))
					ft_exec_export(cmd[c], 2);
				else if (!ft_check_ravno(cmd[c]) && !ft_exp_exist(cmd[c]))
					ft_exec_export(cmd[c], 3);
			}
			else
				i = 1;
			c++;
		}
	}
	if (i == 0)
		ft_exst(0);
}