/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:32:13 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 01:59:53 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_second(char *cmd, int end)
{
	char	*ret;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(cmd);
	if (!cmd || end == len)
		return (NULL);
	ret = ft_calloc(sizeof(char *), ft_strlen(cmd) - end + 1);
	if (!ret)
		return (NULL);
	while (cmd[end + j])
	{
		ret[j] = cmd[end + j];
		j++;
	}
	return (ret);
}

char	*ft_get_env(char *cmd, int start, int end)
{
	int		j;
	char	*compare;
	t_list	*tmp;
	char	*val;

	j = 0;
	tmp = g_glv.env;
	compare = ft_calloc(sizeof(char), end - start + 1);
	if (!compare)
		return (0);
	while (start < end)
		compare[j++] = cmd[start++];
	compare[j] = '\0';
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(compare, tmp->name) == 0)
		{
			val = ft_strdup(tmp->value);
			free(compare);
			return (val);
		}
		tmp = tmp->link;
	}
	free(compare);
	return (NULL);
}

char	*ft_dollar_errors(char *s1, char *s2, char *s3)
{
	if (!s1)
		return (ft_strcat(s2, s3));
	else if (!s3)
		return (ft_strcat(s1, s2));
	return (NULL);
}
