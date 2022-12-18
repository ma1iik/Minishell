/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4 copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:06:40 by misrailo         ###   ########.fr       */
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
