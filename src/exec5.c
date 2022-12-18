/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:23:33 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
