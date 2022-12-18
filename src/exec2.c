/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:05:26 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
