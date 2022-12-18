/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:01:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 05:23:26 by misrailo         ###   ########.fr       */
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
	str = ft_calloc(sizeof(char), ft_strlen(lst->name)
			+ ft_strlen(lst->value) + 2);
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
