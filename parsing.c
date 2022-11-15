/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:45:05 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/13 20:13:03 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_closed(char c_char, int ii, t_data *data)
{
	char	c;
	int		i;

	c = c_char;
	if ((data->cmd[ii + 1]) == '\0')
	{
        printf ("quotes didnt close\n");
		return (-1);
	}
    else
		i = ii + 1;
	while (data->cmd[i] && data->cmd[i] != c)
		i++;
	if (data->cmd[i] == c)
	{
		printf("closed succesfully\n");
		return (i);
	}
	else
	{
		printf ("quotes didnt close\n");
		return (-1);
	}
}

int	ft_logic_groups(t_data *data, int i, int pipes)
{
	while (ft_isspace(data->cmd[i]))
		i++;
	while (data->cmd[i] != '\0')
	{
		if (data->cmd[i] != '|')
		{
			while (data->cmd[i] != '|' && data->cmd[i] != '\0')
			{
				if (data->cmd[i] == '"' || data->cmd[i] == '\'')
				{;
					i = ft_check_if_closed(data->cmd[i], i, data);
                    if (i == -1)
						return (0);
				}
				i++;
			}
			data->groups += 1;
            //printf("logic groups ---> %d\n", data->groups);
		}
		if (data->cmd[i] == '|')
		{
			while (ft_isspace(data->cmd[i + 1]))
				i++;
			if (data->cmd[i + 1] == '|')
				return (0);
			pipes += 1;
			i++;
		}
		if (data->cmd[i + 1] == '\0')
			break ;
	}
	if (pipes + 1 == data->groups)
		return (1);
	else if (pipes == 0 && data->groups == 0)
		return (0);
	printf("Wrong pipe usage error\n");
	return (0);
}

int ft_one_group_function(t_data *data, int grp_nb, int ii)
{
    int i;
    int j;
    int start;
        
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

int	ft_save_groups(t_data *data, int grp_nbr, int ii)
{
	int	i;
	int	j;
	int	grp_nb;
	int	start;
	char	c_char;

	grp_nb = grp_nbr + 1;//3 ---> right amount of groups
	i = ii;// ii = 0 
	j = 0;
    start = i;
    if (grp_nb == data->groups)
		return (0);
	if (data->groups == 1 || grp_nb + 1 == data->groups)
		ft_one_group_function(data, grp_nb, i);
	else
    {        
        while (data->cmd[i] && grp_nb < data->groups)
        {
            if (data->cmd[i] && data->cmd[i] == '|')
            {
                data->cmd_tab[grp_nb] = ft_calloc(j + 1, sizeof(char));
                ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
                //printf("logic grouop %d is %s\ngroups exist - %d\n", grp_nb, data->cmd_tab[grp_nb], data->groups);
                i++;
                ft_save_groups(data, grp_nb, i);
                return (0);
            }
            else if (data->cmd[i] && (data->cmd[i] == '"' || data->cmd[i] == '\''))
            {
				c_char = data->cmd[i];
                i++;
                while (data->cmd[i] && (data->cmd[i] != c_char))
                {
                    i++;
                    j++;
                }
                i++;
                j = j + 2;
            }
            else if (data->cmd[i] && data->cmd[i] != '|' && data->cmd[i] != '"' && data->cmd[i] != '\'' )
            {
                while (data->cmd[i] && data->cmd[i] != '|' && data->cmd[i] != '"' && data->cmd[i] != '\'' )
                {
                    i++;
                    j++;
                }
            }
        }
    }
    return(0);
}

int	ft_custom_split(t_data *data)
{
	data->groups = 0;
	if (!ft_logic_groups(data, 0, 0))
		return (0);
	data->cmd_tab = ft_calloc(data->groups, sizeof(char *));
	ft_save_groups(data, -1, 0);
	// {		
	// }
	return (1);
	//should return **char
}
