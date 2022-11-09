/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/07 23:08:01 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_lexer(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->groups)
	{
		if (!data->cmd_tab[i])
			break;
		init_lexer(data);
		get_next_token(data);
		ft_rm_quotes(data);
		i++;
	}
	//print_tok(data);
}

void	ft_init_data(t_data *data)
{
	data->exit_t = 1;
	data->env_f = 1;
	data->cmd_n = 0;
}

void	read_line(t_data *data)
{
	ft_init_data(data);
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		add_history(data->cmd);
		if (!ft_custom_split(data))
		{
			continue;
		}
		print_cmd(data);
		ft_lexer(data);
		
		// print your cmd
	}
	data->exit_t = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	ft_create_env(data->env, env);
	read_line(data);
    //parse_line(data);
	ft_dealloc_env(&data->env);
    // execute_line();
	return (0);
}
