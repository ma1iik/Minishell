/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils copy 2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 12:17:28 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_g_glv(char **env, int num)
{
	int		i;
	t_list	*tmp;

	i = 0;
	if (num == 1)
		tmp = g_glv.env;
	else if (num == 2)
		tmp = g_glv.env_exp;
	while (env[i])
	{
		tmp->name = ft_get_name(env[i]);
		tmp->value = ft_get_val(env[i]);
		i++;
		tmp = tmp->link;
	}
	tmp->name = ft_strdup("?");
	tmp->value = ft_strdup("0");
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_fill_envstr(t_data *data, char **env)
{
	int		len;
	int		i;

	len = ft_tab_len(env);
	data->env_str = ft_calloc(sizeof(char *), len + 2);
	i = 0;
	while (i < len)
	{
		data->env_str[i] = ft_strdup(env[i]);
		i++;
	}
	data->env_str[i] = ft_strdup("?=0");
}

char	*ft_get_val(char *env)
{
	int		j;
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	j = i + 1;
	while (env[j] != '\0' && env[j] != '\n')
	{
		len++;
		j++;
	}
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	dest = ft_strncpy(dest, &env[i + 1], len);
	return (dest);
}

char	*ft_get_name(char *env)
{
	int		i;
	char	*dest;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	dest = ft_calloc(sizeof(char), i + 1);
	if (!dest)
		return (0);
	dest = ft_strncpy(dest, env, i);
	return (dest);
}
