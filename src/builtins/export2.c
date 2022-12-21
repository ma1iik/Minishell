/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:02:21 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:02:25 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_exp(void)
{
	t_list	*tmp;

	tmp = g_glv.env_exp;
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
	while (s[len] != '=' && s[len] != '\0')
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

int	ft_exp_exist(char *s)
{
	char	*name;
	t_list	*tmp;

	tmp = g_glv.env_exp;
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
