/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:58:09 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:12:01 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(t_data *data, int x)
{
	int		cnt;
	int		arg;

	cnt = 0;
	arg = 0;
	while (data->tokens[x].e_type && data->tokens[x].e_type != PIPE
		&& data->tokens[x].e_type != END)
	{
		if (data->tokens[x].e_type < 5 || data->tokens[x].e_type == 6)
			arg = 1;
		else if (!arg && (data->tokens[x].e_type == ARG
				|| data->tokens[x].e_type == CMD))
		{
			cnt++;
		}
		x++;
	}
	return (cnt);
}

char	**ft_get_args(t_data *data, t_cmdl *tmp)
{
	char	**args;
	int		arg_c;
	int		i;
	int		arg;

	i = 0;
	arg = 0;
	arg_c = ft_count_arg(data, data->cmdl_i) + 1;
	args = ft_calloc(sizeof(char *), arg_c);
	while (data->tokens[data->cmdl_i].e_type && data->tokens[data->cmdl_i].e_type != PIPE
		&& data->tokens[data->cmdl_i].e_type != END && i < arg_c)
	{
		if (!arg && (data->tokens[data->cmdl_i].e_type == CMD || data->tokens[data->cmdl_i].e_type == ARG))
		{
			if (data->tokens[data->cmdl_i].e_type == CMD)
				tmp->nocmd = 0;
			args[i] = ft_strdup(data->tokens[data->cmdl_i].value);
			i++;
		}
		else if (data->tokens[data->cmdl_i].e_type < 5 || data->tokens[data->cmdl_i].e_type == 6)
			arg = 1;
		data->cmdl_i++;
	}
	args[i] = NULL;
	return (args);
}

t_cmdl	*ft_lst_cmdl(t_cmdl *cmdl)
{
	if (!cmdl)
		return (NULL);
	while (cmdl->next)
		cmdl = cmdl->next;
	return (cmdl);
}

void	ft_addback_cmdl(t_cmdl **cmd, t_cmdl *new)
{
	t_cmdl	*lst;

	if (!*cmd)
	{
		new->pos = 1;
		*cmd = new;
		return ;
	}
	lst = ft_lst_cmdl(*cmd);
	new->pos = lst->pos + 1;
	if (new->pos != 1)
		new->prev = lst;
	else
		new->prev = NULL;
	lst->next = new;
}

int	ft_count_red(t_data *data, int x)
{
	int		cnt;
	int		arg;

	cnt = 0;
	arg = 0;
	while (data->tokens[x].e_type && data->tokens[x].e_type != PIPE && data->tokens[x].e_type != END)
	{
		if (!arg && (data->tokens[x].e_type < 5 || data->tokens[x].e_type == 6))
		{
			arg = 1;
			cnt++;
		}
		else if (arg && (data->tokens[x].e_type < 5 || data->tokens[x].e_type == 6 || data->tokens[x].e_type == 8))
			cnt++;
		x++;
	}
	return (cnt);
}

char	**ft_get_redir(t_data *d, int i, int arg)
{
	char	**redirs;
	int		red_c;
	int		p;

	p = d->cmdl_i;
	red_c = ft_count_red(d, d->cmdl_i) + 1;
	redirs = ft_calloc(sizeof(char *), red_c);
	while (d->tokens[p].e_type && d->tokens[p].e_type != PIPE
		&& d->tokens[p].e_type != END && i < red_c)
	{
		if (!arg && (d->tokens[p].e_type < 5
				|| d->tokens[p].e_type == 6))
		{
			redirs[i] = ft_strdup(d->tokens[p].value);
			i++;
			arg = 1;
		}
		else if ((arg && (d->tokens[p].e_type < 5
					|| d->tokens[p].e_type == 6 || d->tokens[p].e_type == 8)))
			redirs[i++] = ft_strdup(d->tokens[p].value);
		p++;
	}
	redirs[i] = NULL;
	return (redirs);
}

t_cmdl	*ft_cmdl_new(t_data *data)
{
	t_cmdl	*tmp;
	int		x;

	x = data->cmdl_i;
	tmp = ft_calloc(sizeof(t_cmdl), 1);
	tmp->nocmd = 1;
	tmp->redir = ft_get_redir(data, 0, 0);
	tmp->cmd = ft_get_args(data, tmp);
	tmp->nb_args = ft_count_arg(data, x);
	tmp->in = STDIN_FILENO;
	tmp->out = STDOUT_FILENO;
	tmp->exit = 0;
	return (tmp);
}

void	ft_set_cmdl(t_data *data)
{
	ft_addback_cmdl(&data->cmd_l, ft_cmdl_new(data));
}

void	ft_fill_cmdl(t_data *data)
{
	data->cmdl_i = 0;
	while (data->cmdl_i < data->tok_nb && data->tokens[data->cmdl_i].e_type != END)
	{
		if (data->tokens[data->cmdl_i].e_type == PIPE)
			data->cmdl_i++;
		else if (!data->tokens)
			return ;
		else
			ft_set_cmdl(data);
	}
}