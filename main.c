/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/03 14:31:53 by ma1iik           ###   ########.fr       */
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
	print_tok(data);
}

void	read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		add_history(data->cmd);
		if (!ft_custom_split(data))
		{
			printf("here\n");
			continue;
		}
		print_cmd(data);
		ft_lexer(data);
		
		// print your cmd
	}
	data->exit_t = 0;
}

void	print_env(t_list *head)
{
	t_list *tmp;

	tmp = head;
	printf("LOL\n");
	while (tmp->link != NULL)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->link;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	ft_create_env(data->env, env);
	print_env(data->env);
	read_line(data);

    //parse_line(data);
    // execute_line();
	return (0);
}
