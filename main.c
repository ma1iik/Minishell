/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/15 04:29:14 by misrailo         ###   ########.fr       */
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
	if (!get_next_token(data))
		return (0);
	ft_rm_quotes(data);
	return (1);
}

void	ft_init_data(t_data *data)
{
	data->exit_t = 1;
	data->env_f = 1;
	data->cmd_n = 0;
	data->error_str = NULL;
}

void	ft_func()
{
	t_list	*tmp;

	tmp = g_glv.env_exp;
	while (tmp != NULL)
	{
		if (ft_strcmp("USER", tmp->name) == 0)
		{
			tmp->value = ft_strdup("LOH");
		}
		tmp = tmp->link;
	}
}

void	read_line(t_data *data)
{
	ft_init_data(data);
	while (1)
	{
		signal(SIGINT, ft_sig_exec1);
		signal(SIGQUIT, ft_sig_exec1);
		//ft_func();
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
		ft_print_err(data);
		ft_free_all(data);
		free(data->cmd);
	}
}

void	ft_g_glv(char **env, t_data *data)
{
	g_glv.env = ft_calloc(sizeof(t_list), 1);
	g_glv.env_exp = ft_calloc(sizeof(t_list), 1);
	g_glv.redsig = 1;
	g_glv.heredoc = 0;
	g_glv.env_sig = 0;
	int		len;
	int		i;
	
	(void)data;
	i = 0;
	len = ft_tab_len(env);
	ft_fill_envstr(data, env);
	while (i < len + 1)
	{
		ft_lstadd_back(&g_glv.env, ft_lstnew(env[i]));
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_lstadd_back(&g_glv.env_exp, ft_lstnew(env[i]));
		i++;
	}
	// ft_lstadd_back(&g_glv.env, ft_lstnew_last());
	ft_fill_g_glv(env, 1);
	ft_fill_g_glv(env, 2);
}

void		ft_print_g_glv(void)
{
	t_list *tmp;

	tmp = g_glv.env;
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
	ft_g_glv(env, data);
	//ft_print_g_glv();
	read_line(data);
	ft_free_envstr(data);
	//ft_dealloc_envstr(data);
    //parse_line(data);
	//ft_dealloc_env(data);
    // execute_line();
	return (0);
}
