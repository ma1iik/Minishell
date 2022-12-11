/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:58:09 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/11 17:13:06 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_arg(t_data *data, int x)
{
	int		cnt;

	cnt = 0;
	while (data->tokens[x].e_type && data->tokens[x].e_type != PIPE && data->tokens[x].e_type != END)
	{
		if (data->tokens[x].e_type == ARG || data->tokens[x].e_type == CMD)
			cnt++;
		x++;
	}
	return (cnt);
}

char	**ft_get_args(t_data *data)
{
	char	**args;
	int		arg_c;
	int		i;

	i = 0;
	arg_c = ft_count_arg(data, data->cmdl_i) + 1;
	// printf("arg count is %d\n", arg_c);
	args = ft_calloc(sizeof(char *), arg_c);
	while (data->tokens[data->cmdl_i].e_type && data->tokens[data->cmdl_i].e_type != PIPE
		&& data->tokens[data->cmdl_i].e_type != END && i < arg_c)
	{
		if (data->tokens[data->cmdl_i].e_type == CMD || data->tokens[data->cmdl_i].e_type == ARG)
		{
			args[i] = ft_strdup(data->tokens[data->cmdl_i].value);
			// printf("get args is -->%s\n", args[i]);
			i++;
		}
		data->cmdl_i++;
	}
	args[i] = NULL;
	// if (data->tokens[data->cmdl_i].e_type == END)
	// 	data->cmdl_i++;
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
	//printf("new CMD --> %s", new->cmd[0]);
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

	cnt = 0;
	while (data->tokens[x].e_type && data->tokens[x].e_type != PIPE && data->tokens[x].e_type != END)
	{
		if (data->tokens[x].e_type < 5|| data->tokens[x].e_type == 6)
			cnt++;
		x++;
	}
	return (cnt);
}

char	**ft_get_redir(t_data *data)
{
	char	**redirs;
	int		red_c;
	int		i;
	int		place;

	i = 0;
	place = data->cmdl_i;
	red_c = ft_count_red(data, data->cmdl_i) + 1;
	// printf("red count is %d\n", red_c);
	redirs = ft_calloc(sizeof(char *), red_c);
	while (data->tokens[place].e_type && data->tokens[place].e_type != PIPE
		&& data->tokens[place].e_type != END && i < red_c)
	{
		if (data->tokens[place].e_type < 5 || data->tokens[place].e_type == 6)
		{
			redirs[i] = ft_strdup(data->tokens[place].value);
			// printf("get args is -->%s\n", args[i]);
			i++;
		}
		place++;
	}
	redirs[i] = NULL;
	// if (data->tokens[data->cmdl_i].e_type == END)
	// 	data->cmdl_i++;
	return (redirs);
}

t_cmdl	*ft_cmdl_new(t_data *data)
{
	t_cmdl	*tmp;
	int		x;

	x = data->cmdl_i;
	tmp = ft_calloc(sizeof(t_cmdl), 1);
	tmp->rerdir = ft_get_redir(data);
	tmp->cmd = ft_get_args(data);
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
	//ft_free_all(data);
}