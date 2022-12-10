/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/11 00:47:36 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_pipe(t_cmdl *cmd)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
		{
			perror("pipe error");
			return ;
		}
	}
	return ;
}

int	ft_tlsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->link;
		i++;
	}
	return (i);
}

char	*ft_combine_envvars(t_data *data, t_list *lst)
{
	//int		len;
	char	*str;

	(void)data;
	str = ft_calloc(sizeof(char), ft_strlen(lst->name) + ft_strlen(lst->value) + 2);
	str = ft_strcat1(str, lst->name);
	str = ft_strcat1(str, "=");
	str = ft_strcat1(str, lst->value);
	return (str);
}

char	**ft_dum_env_unset(t_data *data)
{
	int		i;
	t_list	*tmp;
	char	**ret;

	i = 0;
	ret = calloc(sizeof(char *), (ft_tlsize(glv.env) + 1));
	tmp = glv.env;
	while (tmp && (ft_strcmp(tmp->name, "?") != 0))
	{
		ret[i] = ft_combine_envvars(data, tmp);
		i++;
		tmp = tmp->link;
	}
	ret[i] = ft_strdup("?=0");
	free(tmp);
	return (ret);
}

char	*ft_cur_var(char *cur, char **sp_path, int i, t_cmdl *cmd)
{
	char	*tmp;
	// cur =   ft_calloc(sizeof(char),
	//   		(ft_strlen(sp_path[i]) + ft_strlen((*cmd).cmd[0]) + 2));
	// cur = ft_strcat1(cur, sp_path[i]);
	// cur = ft_strcat1(cur, "/");
	// cur = ft_strcat1(cur, (*cmd).cmd[0]);
	tmp = ft_strcat(sp_path[i], "/");
	cur = ft_strcat(tmp, (*cmd).cmd[0]);
	free (tmp);
	return (cur);
}

char	**ft_cur_var1(t_data *data, char **sp_path, int i, t_cmdl *cmd)
{
	//int		len;
	char	*name;
	char	**cur;
	int		len2;
	int		j;
	char	*tmp;

	(void)cmd;
	j = 1;
	len2 = ft_tab_len(data->cmd_l->cmd);
	//len = ft_strlen(data->cmd_l->cmd[0]);
	name = ft_strdup(data->cmd_l->cmd[0]);
	cur = ft_calloc(sizeof(char *), len2 + 1);
	//cur[0] = ft_calloc(sizeof(char), (ft_strlen(sp_path[i]) + len + 2));
	//cur[0] = ft_strcat(cur[0], sp_path[i]);
	tmp = ft_strcat(sp_path[i], "/");
	cur[0] = ft_strcat(tmp, name);
	while (j < len2)
	{
		cur[j] = ft_strdup(data->cmd_l->cmd[j]);
		j++;
	}
	cur[j] = NULL;
	ft_free_2d(data->cmd_l->cmd);
	free (name);
	free (tmp);
	return (cur);
}

void	ft_arrange_path(t_cmdl *cmd, t_data *data)
{
	char	*path;
	char	**splitted;
	char	*cur;
	int		i;

	i = 0;
	cur = NULL;
	path = getenv("PATH");
	if ((access((cmd)->cmd[0], F_OK) == 0) || ft_isbuiltin(data))
		return ;
	else if (cmd->cmd[0][0] != '/' && (cmd->cmd[0][0] != '.' && cmd->cmd[0][1] != '/'))
	{
		splitted = ft_split(path, ':');
		while (splitted[i])
		{
			cur = ft_cur_var(cur, splitted, i, cmd);
			if (access(cur, F_OK) == 0)
			{
				free (data->cmd_l->cmd[0]);
				data->cmd_l->cmd[0] = cur;
				ft_free_2d(splitted);
				//free (cur);
				return ;
			}
			//free (cur);
			i++;
		}
	}
	ft_free_2d(splitted);
}

void	ft_check_path(t_data *data)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	len = ft_tab_len(data->env_str);
	if (glv.env_sig == 1)
	{
		ft_free_2d(data->env_str);
		data->env_str = ft_dum_env_unset(data);
		glv.env_sig = 0;
	}
	str = ft_strjoin("PATH=", getenv("PATH"));
	while (data->env_str[i] && i < len)
	{
		if (!ft_strcmp(str, data->env_str[i]))
			ft_arrange_path(data->cmd_l, data);
		i++;
	}
	free (str);
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
		printf("closed1\n\n\n\n");
	}
	if (cmd->prev)
	{
		close(cmd->prev->pipe[0]);
		printf("closed2\n\n\n\n");
	}
}

void	ft_exec_err(t_data *data, int errn, char **env)
{
	ft_free_2d(env);
	if (errn == EACCES)
		ft_exst(126);
	if (errn == ENOENT)
		ft_exst(127);
	if (errn == 127)
		printf("%s: command not found\n", data->cmd_l->cmd[0]);
	else if (errn == 126)
		printf("%s: argument found but not executable\n", data->cmd_l->cmd[0]);
	// else if (errn == 1)
	// 	printf("%s: No such file or directory\n", cmd);
	ft_free_all(data);
	exit(EXIT_FAILURE);
}

void	ft_exbuiltin(t_data *data)
{
	if (!ft_strcmp(data->cmd_l->cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(data->cmd_l->cmd[0], "cd"))
	{
		ft_cd(data->cmd_l->cmd);
	}
	else if (!ft_strcmp(data->cmd_l->cmd[0], "export"))
		ft_export(data->cmd_l->cmd, 1);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "env"))
		ft_env();
	else if (!ft_strcmp(data->cmd_l->cmd[0], "unset"))
		ft_unset(data->cmd_l->cmd);
	else if (!ft_strcmp(data->cmd_l->cmd[0], "echo"))
		ft_echo(data->cmd_l->cmd);
}

void	ft_execcmd(t_data *data, char **env)
{
	int	execc;

	//printf("EXEC--> %s\n", data->cmd_l->cmd[0]);
	if (ft_isbuiltin(data) == 1)
	{
		ft_exbuiltin(data);
		//ft_free_all(data);
		exit (0);
	}
	else
	{
		execc = execve(data->cmd_l->cmd[0], data->cmd_l->cmd, env);
		if (execc == -1)
		{
			ft_exec_err(data, errno, env);
		}
	}
}

int	ft_child(t_data *data)
{
	int		status;

	ft_check_path(data);
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("fork error");
		return (0);
	}
	if (data->pid == 0)
	{
		ft_pipes(data->cmd_l);
		ft_execcmd(data, data->env_str);
	}
	waitpid(data->pid, &status, 0);
	return (1);
}

int	ft_exec(t_data *data)
{
	signal(SIGINT, ft_sig_exec);
	signal(SIGQUIT, ft_sig_exec);
	//ft_exit_st(0);
	(void)data;
	while (data->cmd_l)
	{
		ft_open_pipe(data->cmd_l);
		if (!ft_child(data))
		{
			return (0);
		}
		ft_close_pipe(data->cmd_l);
		data->cmd_l = data->cmd_l->next;
		
	}
	return (1);
}