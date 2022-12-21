/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/21 20:15:59 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat1(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	ft_free_2d(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}

void	puterr(char *cmd)
{
	printf("%s: command not found\n", cmd);
	ft_exst(127);
	return ;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	a;
	unsigned int	b;
	char			*newstr;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1[a])
	{
		newstr[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		newstr[a + b] = s2[b];
		b++;
	}
	newstr[a + b] = '\0';
	return (newstr);
}

int	ft_isbuiltin(t_data *data)
{
	if (!data->cmd_l->cmd[0])
		return (0);
	if (!ft_strcmp(data->cmd_l->cmd[0], "echo")
		|| !ft_strcmp(data->cmd_l->cmd[0], "env")
		|| !ft_strcmp(data->cmd_l->cmd[0], "pwd"))
		return (2);
	if (!ft_strcmp(data->cmd_l->cmd[0], "cd")
		|| !ft_strcmp(data->cmd_l->cmd[0], "exit")
		|| !ft_strcmp(data->cmd_l->cmd[0], "export")
		|| !ft_strcmp(data->cmd_l->cmd[0], "unset"))
		return (1);
	return (0);
}
