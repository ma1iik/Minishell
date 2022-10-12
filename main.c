/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/12 20:50:11 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_logic_groups(char *cmd, int i, int pipes, int groups)
{
	while (ft_isspace(cmd[i]))
		i++;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != '|')
		{
			while (cmd[i] != '|' && cmd[i + 1] != '\0')
				i++;
			groups += 1; 
		}
		if (cmd[i] == '|')
		{
			while (ft_isspace(cmd[i + 1]))
				i++;
			if (cmd[i + 1] == '|')
				return (0);
			pipes += 1;
			i++;
		}
		if (cmd[i + 1] == '\0')
			break;
	}
	if (pipes + 1 == groups)
		return (1);
	return (0);
}

int ft_custom_split(char * cmd)
{
	int	 i;
	
	i = 0;
	char **sptil_cmds;
	if (!ft_logic_groups(cmd, 0, 0, 0))
	{
		printf("BAD GROUPS\n");
		exit(EXIT_FAILURE);
	}
	while (cmd[i])
	{
				
	}
	return (0);
	////should return **char
}

void read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		//data->cmd_tab = 
		ft_custom_split(data->cmd);
	}
	data->exit_t = 0;
}

int main(void)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
    read_line(data);
    //parse_line(data);
    // execute_line();
	
	return (0);
}
