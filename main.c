/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/27 23:12:57 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int init_lexer(t_data *data)
{
	data->lexer.index = 0;
	data->lexer.i = 0;
	data->lexer.c = data->lexer.content[0];
}

void	lexer_advance(t_data *data)
{
	if (data->lexer.c != '\0' && data->lexer.i < ft_strlen(data->lexer.content))
}

void	make_exec(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->groups)
	{
		if (!data->cmd_tab[i])
		init_lexer(data);
		get_next_token(data);
	}
}

void	read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		add_history(data->cmd);
		if (!ft_custom_split(data))
			continue;
		print_cmd(data);
		make_exec(data);
		
		// print your cmd
	}
	data->exit_t = 0;
}

int	main(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	read_line(data);

    //parse_line(data);
    // execute_line();
	return (0);
}
