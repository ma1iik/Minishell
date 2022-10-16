/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malik <malik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/13 18:25:17 by malik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_logic_groups(t_data *data, int i, int pipes)
{
	while (ft_isspace(data->cmd[i]))
		i++;
	while (data->cmd[i] != '\0')
	{
		if (data->cmd[i] != '|')
		{
			while (data->cmd[i] != '|' && data->cmd[i + 1] != '\0')
				i++;
			data->groups += 1; 
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
			break;
	}
	if (pipes + 1 == data->groups)
		return (1);
	return (0);
}

int	ft_save_groups(t_data *data, int grp_nbr)
{
	int	i;
	int j;
	int grp_nb;

	grp_nb = grp_nbr + 1;
	i = 0;
	j = 0;
	while (data->cmd[i])
	{
		while(ft_isspace(data->cmd[i]))
			i++;
		while(data->cmd[i] != '|')
			j++;
		data->cmd_tab[grp_nb] = ft_calloc(j, sizeof(char));
		ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[i], j);
		printf("logic grouop %d is %s\n", grp_nb, data->cmd_tab[grp_nb]);
		i++;
		ft_save_groups(data, grp_nb);
	}
	return (0);
}

int ft_custom_split(t_data *data)
{
	int	 i;
	
	i = 0;
	if (!ft_logic_groups(data, 0, 0))
	{
		printf("BAD GROUPS\n");
		exit(EXIT_FAILURE);
	}
	data->cmd_tab = ft_calloc(data->groups, sizeof(char *));
	ft_save_groups(data, -1);
	// {		
	// }
	return (0);
	//should return **char
}

void read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		//data->cmd_tab = 
		ft_custom_split(data);
	}
	data->exit_t = 0;
}

int main(void)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	printf("\ndata struct is %lu\ncmd aka one pointer is %lu\ncmds or 2 pointers is %lu\nsize of int is %lu\n", sizeof(t_data), sizeof(data->cmd), sizeof(data->cmd_tab), sizeof(data->exit_t));
    read_line(data);
    //parse_line(data);
    // execute_line();
	
	return (0);
}
