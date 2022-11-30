/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:06:24 by ma1iik            #+#    #+#             */
/*   Updated: 2022/11/26 08:16:21 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exst(int num)
{
	t_list	*tmp;

	tmp = glv.env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "?") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(ft_itoa(num));
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
	}
	if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

void		ft_sig_exec(int sig)
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
	if (data->lexer.content[data->lexer.i + 1 == '<'])
	{
		ft_init_tok(data, DL_RED, "<<");
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			printf("Parse error near `%s'\n'", "<<");
			return (0);
		}
	}
	else
	{
		ft_init_tok(data, L_RED, "<");
		if (!ft_token_filename(data))
		{
			printf("Parse error near `%s'\n'", "<");
			return (0);
		}
	}
	lexer_advance(data);
	return (1);
}


int	ft_token_r_red (t_data *data)
{
	if (data->lexer.content[data->lexer.i + 1 == '>'])
	{
		ft_init_tok(data, DL_RED, ">>");
		lexer_advance(data);
		if (!ft_token_filename(data))
		{
			printf("Parse error near `%s'\n'", ">>");
			return (0);
		}
	}
	else
	{
		ft_init_tok(data, L_RED, ">");
		if (!ft_token_filename(data))
		{
			printf("Parse error near `%s'\n'", ">");
			return (0);
		}
	}
	lexer_advance(data);
	return (1);
}