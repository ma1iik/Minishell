/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:45:05 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/21 22:36:59 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_one_group_function(t_data *data, int grp_nb, int ii)
{
	int		i;
	int		j;
	int		start;

	i = ii;
	j = 0;
	while (ft_isspace(data->cmd[i]))
		i++;
	start = i;
	while (data->cmd[i])
	{
		i++;
		j++;
	}
	data->cmd_tab[grp_nb] = ft_calloc(j + 1, sizeof(char));
	ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
	return (0);
}

int	ft_onlysp(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	if (s != NULL)
		free (s);
	return (1);
}

int	ft_inv_char(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		else if (str[i] == ';' || str[i] == '\\')
		{
			printf("Error: invalid character\n");
			return (0);
		}
		i++;
	}
	return (1);
}
