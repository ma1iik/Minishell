/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:53 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ret = calloc(sizeof(char *), (ft_tlsize(g_glv.env) + 1));
	tmp = g_glv.env;
	while (tmp && (ft_strcmp(tmp->name, "?") != 0))
	{
		ret[i] = ft_combine_envvars(data, tmp);
		i++;
		tmp = tmp->link;
	}
	ret[i] = ft_strdup("?=0");
	return (ret);
}

char	*ft_cur_var(char **sp_path, int i, t_cmdl *cmd)
{
	char	*tmp;
	char	*cur;

	tmp = ft_strcat(sp_path[i], "/");
	cur = ft_strjoin(tmp, cmd->cmd[0]);
	free (tmp);
	return (cur);
}

char	**ft_cur_var1(t_data *data, char **sp_path, int i, t_cmdl *cmd)
{
	char	*name;
	char	**cur;
	int		len2;
	int		j;
	char	*tmp;

	(void)cmd;
	j = 1;
	len2 = ft_tab_len(data->cmd_l->cmd);
	name = ft_strdup(data->cmd_l->cmd[0]);
	cur = ft_calloc(sizeof(char *), len2 + 1);
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

int	try_splitted(t_data *data, int i, char ***splitted, t_cmdl *cmd)
{
	char	*cur;

	cur = ft_cur_var(*splitted, i, cmd);
	if (access(cur, F_OK) == 0)
	{
		free (data->cmd_l->cmd[0]);
		data->cmd_l->cmd[0] = ft_strdup(cur);
		ft_free_2d(*splitted);
		free (cur);
		return (0);
	}
	else
		free (cur);
	return (1);
}

int	ft_arrange_path(t_cmdl *cmd, t_data *data)
{
	char	*path;
	char	**splitted;
	int		i;

	i = 0;
	splitted = NULL;
	if (cmd->nocmd == 1)
		return (0);
	path = getenv("PATH");
	if ((access((cmd)->cmd[0], F_OK) == 0) || ft_isbuiltin(data))
		return (0);
	else if (cmd->cmd[0][0] != '/' && (cmd->cmd[0][0] != '.'
		&& cmd->cmd[0][1] != '/'))
	{
		splitted = ft_split(path, ':');
		while (splitted[i])
		{
			if (!try_splitted(data, i, &splitted, cmd))
				return (0);
			i++;
		}
	}
	ft_free_2d(splitted);
	return (1);
}

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

void	ft_execcmd(t_data *data, char **env)
{
	int	execc;

	if (ft_isbuiltin(data) == 1)
	{
		ft_exbuiltin(data);
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

int	ft_check_redir(t_data *data)
{
	int	i;

	if (data->cmd_l->redir[0] != NULL)
	{
		if (data->cmd_l->redir[1] == NULL)
		{
			g_glv.redsig = 0;
			return (0);
		}
		i = 3;
		if (data->cmd_l->redir[2] != NULL)
		{
			while (i <= ft_tab_len(data->cmd_l->redir))
			{
				if (data->cmd_l->redir[i] == NULL)
				{
					g_glv.redsig = 0;
					return (0);
				}
				i += 2;
			}
		}
	}
	return (1);
}

char	*ft_get_errstr(t_data *data)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	if (!data->cmd_l->redir[2])
		return (NULL);
	tmp1 = ft_strjoin(data->cmd_l->cmd[0], ": cannot access '");
	tmp2 = ft_strjoin(tmp1, data->cmd_l->redir[2]);
	str = ft_strjoin(tmp2, "': No such file or directory\n");
	free (tmp1);
	free (tmp2);
	return (str);
}

void	ft_add_error(t_data *data, int rows, char *str)
{
	char	**dest;
	int		i;

	i = 0;
	dest = ft_calloc(rows + 2, sizeof(char *));
	while (data->error_str[i])
	{
		dest[i] = ft_strdup(data->error_str[i]);
		i++;
	}
	dest[i] = ft_strdup(str);
	i++;
	dest[i] = NULL;
	ft_free_2d(data->error_str);
	data->error_str = dest;
}

void	ft_errstr(t_data *data)
{
	char	*err;

	err = NULL;
	if (!data->error_str)
	{
		data->error_str = ft_calloc(sizeof(char *), 2);
		data->error_str[0] = ft_get_errstr(data);
		data->error_str[1] = NULL;
	}
	else
	{
		err = ft_get_errstr(data);
		ft_add_error(data, ft_tab_len(data->error_str), err);
	}
	free (err);
}

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
