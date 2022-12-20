/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/20 18:50:04 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lexer(t_data *data)
{
	init_lexer(data);
	if (!ft_dollar_rules(data))
		return (0);
	data->lexer.content = data->cmd;
	data->lexer.c = data->lexer.content[0];
	if (!get_next_token(data, 0))
		return (0);
	ft_rm_quotes(data, 0, 0);
	return (1);
}

void	ft_init_data(t_data *data)
{
	data->lg_p = 0;
	data->lg_i = 0;
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
			break ;
		if (ft_onlysp(data->cmd))
			continue ;
		if (!ft_custom_split(data))
			continue ;
		if (data->cmd)
			add_history(data->cmd);
		if (!ft_lexer(data))
			continue ;
		if (!ft_rules(data))
			continue ;
		ft_fill_cmdl(data);
		data->cmd_l_free = data->cmd_l;
		if (!ft_exec(data))
			continue ;
		ft_free_all(data);
		free(data->cmd);
	}
}

void	ft_g_glv(char **env, t_data *data)
{
	int		len;
	int		i;

	g_glv.env = ft_calloc(sizeof(t_list), 1);
	g_glv.env_exp = ft_calloc(sizeof(t_list), 1);
	g_glv.redsig = 1;
	g_glv.heredoc = 0;
	g_glv.env_sig = 0;
	(void)data;
	i = 0;
	len = ft_tab_len(env);
	ft_fill_envstr(data, env);
	while (i < len)
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
	ft_fill_g_glv(env, 1);
	ft_fill_g_glv(env, 2);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	ft_g_glv(env, data);
	read_line(data);
	ft_free_envstr(data);
	return (0);
}
