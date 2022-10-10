/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/10 20:47:55 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_logic_groups(char *cmd)
{
	
	return (0);
	return (1);
}
char **ft_custom_plit(char * cmd)
{
	int	 i;
	char **sptil_cmds;
	if (!ft_logic_groups(cmd))
		exit(EXIT_FAILURE);
	.
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '|')
			i++;
		else 
			
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total;

	total = count * size;
	str = malloc(total);
	if (!str)
		return (NULL);
	ft_memset(str, 0, total);
	return (str);
}

void read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		//data->cmd_tab = ft_custom_plit(data->cmd);
	}
}

//parse

int main(void)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
    read_line(data);
    //parse_line(data);
    // execute_line();
}