/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 04:54:02 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_child(t_data *data)
{
	int		status;
	int		exit_code;

	ft_check_path(data);
	ft_check_redir(data);
	if (!g_glv.redsig)
		ft_errstr(data);
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("fork error");
		return (0);
	}
	if (data->pid == 0 && g_glv.redsig)
	{
		ft_pipes(data->cmd_l);
		ft_redirs(data->cmd_l);
		ft_execcmd(data, data->env_str);
	}
	waitpid(data->pid, &status, 0);
	exit_code = WEXITSTATUS(status);
	ft_exst(exit_code);
	if (!g_glv.redsig)
		g_glv.redsig = 1;
	return (1);
}

void	ft_print_err(t_data *data)
{
	int		i;

	i = 0;
	if (data->error_str != NULL)
	{
		printf ("WTF\n");
		while (data->error_str[i])
		{
			printf("%s", data->error_str[i]);
			i++;
		}
		ft_free_2d(data->error_str);
	}
}

int	exec_cmds(t_data *data)
{
	ft_open_pipe(data->cmd_l);
	if (!ft_child(data))
		return (0);
	ft_close_pipe(data->cmd_l);
	data->cmd_l = data->cmd_l->next;
	return (1);
}

void	print_free_err(char **err)
{
	printf("%s\n", *err);
	free (*err);
}

int	ft_exec(t_data *data, int pth)
{
	char	*err;

	err = NULL;
	pth = ft_check_path(data);
	if (pth && data->groups != 1)
		err = ft_strjoin(data->cmd_l->cmd[0], ": command not found");
	signal(SIGINT, ft_sig_exec);
	signal(SIGQUIT, ft_sig_exec);
	if (data->groups == 1 && ft_isbuiltin(data))
	{
		ft_exbuiltin(data);
		data->freesig = 1;
		return (1);
	}
	else
	{
		while (data->cmd_l)
		{
			if (!exec_cmds(data))
				return (0);
		}
	}
	if (err != NULL)
		print_free_err(&err);
	return (1);
}
