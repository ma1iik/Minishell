/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:06:24 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:52 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exst(int num)
{
	t_list	*tmp;
	char	*n;

	tmp = g_glv.env;
	n = ft_itoa(num);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "?") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(n);
			free (n);
			return ;
		}
		tmp = tmp->link;
	}
	return ;
}

void	ft_sig_exec1(int sig)
{
	if (sig == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exst(1);
	}
	if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_exst(130);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		ft_exst(131);
	}
}

int	ft_token_l_red(t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1] == '<')
	{
		ft_init_tok(data, DL_RED, "<<");
		lexer_advance(data);
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			if (!data->lexer.content[data->lexer.i])
				printf("syntax error near `\\n'\n");
			else
				printf("syntax error near `%c'\n'", data->lexer.content[data->lexer.i]);
			return (0);
		}
	}
	else
	{
		ft_init_tok(data, L_RED, "<");
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			if (!data->lexer.content[data->lexer.i])
				printf("syntax error near `\\n'\n");
			else
				printf("syntax error near `%c'\n'", data->lexer.content[data->lexer.i]);
			return (0);
		}
	}
	return (1);
}

int	ft_token_r_red (t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1] == '>')
	{
		ft_init_tok(data, DL_RED, ">>");
		lexer_advance(data);
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			if (!data->lexer.content[data->lexer.i])
				printf("syntax error near `\\n'\n");
			else
				printf("syntax error near `%c'\n'", data->lexer.content[data->lexer.i]);
			return (0);
		}
	}
	else
	{
		ft_init_tok(data, L_RED, ">");
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			if (!data->lexer.content[data->lexer.i])
				printf("syntax error near `\\n'\n");
			else
				printf("syntax error near `%c'\n'", data->lexer.content[data->lexer.i]);
			return (0);
		}
	}
	return (1);
}

void	ft_sig_herd(int sig)
{
	if (sig == SIGINT)
	{
		if (g_glv.heredoc == 0)
		{
			printf("\e[2K");
			rl_on_new_line();
			rl_redisplay();
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			ft_exst(1);
		}
		else
			exit(1);
	}
	if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}