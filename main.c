/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/10 23:12:55 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexer(t_data *data)
{
	init_lexer(data);
	if (!ft_dollar_rules(data, 0, 0))
		return (0);
	data->lexer.content = data->cmd;
	data->lexer.c = data->lexer.content[0];
	//printf("%s\n", data->cmd);
	if (!get_next_token(data))
		return (0);
	ft_rm_quotes(data);
	//print_tok(data);
	return (1);
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
	while (1)
	{
		signal(SIGINT, ft_sig_exec1);
		signal(SIGQUIT, ft_sig_exec1);
		data->cmd = readline("minishell:");
		if (!data->cmd)
			break;
		if (!ft_custom_split(data))
			continue;
		if (data->cmd)
			add_history(data->cmd);
		if (!ft_lexer(data))
			continue;
		if (!ft_rules(data))
			continue;
		ft_fill_cmdl(data);
		data->cmd_l_free = data->cmd_l;
		if (!ft_exec(data))
			continue;
		ft_free_all(data);
		free(data->cmd);
		// print your cmd
	}
}

void	ft_glv(char **env, t_data *data)
{
	glv.env = ft_calloc(sizeof(t_list), 1);
	glv.env_exp = ft_calloc(sizeof(t_list), 1);
	glv.i = 0;
	glv.env_sig = 0;
	int		len;
	int		i;
	
	(void)data;
	i = 0;
	len = ft_tab_len(env);
	ft_fill_envstr(data, env);
	while (i < len)
	{
		ft_lstadd_back(&glv.env, ft_lstnew(env[i]));
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_lstadd_back(&glv.env_exp, ft_lstnew(env[i]));
		i++;
	}
	// ft_lstadd_back(&glv.env, ft_lstnew_last());
	ft_fill_glv(env, 1);
	ft_fill_glv(env, 2);
}

void		ft_print_glv(void)
{
	t_list *tmp;

	tmp = glv.env;
	while (tmp->link != NULL)
	{
		write(1, tmp->name, sizeof(tmp->name));
		tmp = tmp->link;
	}
}


int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	ft_glv(env, data);
	//ft_print_glv();
	read_line(data);
	ft_free_envstr(data);
	//ft_dealloc_envstr(data);
    //parse_line(data);
	//ft_dealloc_env(data);
    // execute_line();
	return (0);
}
