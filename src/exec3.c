/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:05:31 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_path(t_data *data)
{
	int		i;
	char	*str;
	int		len;
	int		err;

	i = 0;
	len = ft_tab_len(data->env_str);
	if (g_glv.env_sig == 1)
	{
		ft_free_2d(data->env_str);
		data->env_str = ft_dum_env_unset(data);
		g_glv.env_sig = 0;
	}
	str = ft_strjoin("PATH=", getenv("PATH"));
	while (data->env_str[i] && i < len)
	{
		if (!ft_strcmp(str, data->env_str[i]))
			err = ft_arrange_path(data->cmd_l, data);
		i++;
	}
	free (str);
	if (err == 1)
		return (1);
	return (0);
}

void	ft_pipes(t_cmdl *cmd)
{
	dup2(cmd->out, STDOUT_FILENO);
	dup2(cmd->in, STDIN_FILENO);
	if (cmd->next)
	{
		close(cmd->pipe[0]);
		dup2(cmd->pipe[1], cmd->out);
		close(cmd->pipe[1]);
	}
	if (cmd->prev)
	{
		dup2(cmd->prev->pipe[0], cmd->in);
		close(cmd->prev->pipe[0]);
	}
}

void	ft_close_pipe(t_cmdl *cmd)
{
	if (cmd->next)
	{
		close(cmd->pipe[1]);
	}
	if (cmd->prev)
	{
		close(cmd->prev->pipe[0]);
	}
}

void	ft_exec_err(t_data *data, int errn, char **env)
{
	ft_free_2d(env);
	if (errn == EACCES)
		ft_exst(126);
	if (errn == ENOENT)
		ft_exst(127);
	if (errn == EACCES)
		printf("%s: argument found but not executable\n", data->cmd_l->cmd[0]);
	else if (errn == ENOENT)
		printf("%s: command not found\n", data->cmd_l->cmd[0]);
	ft_free_all(data);
	exit(EXIT_FAILURE);
}

void	ft_exbuiltin(t_data *data)
{
	if (!ft_strcmp(data->cmd_l->cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(data->cmd_l->cmd[0], "cd"))
		ft_cd(data, data->cmd_l->cmd, 0);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "export"))
		ft_export(data, data->cmd_l->cmd, 1);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "env"))
		ft_env(data, data->cmd_l->cmd);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "unset"))
		ft_unset(data, data->cmd_l->cmd);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "echo"))
		ft_echo(data, data->cmd_l->cmd);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "exit"))
		ft_exit(data, data->cmd_l->cmd);
}
