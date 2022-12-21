/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:20 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:23 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error_cd(char **cmd, int code)
{
	if (code == 1)
	{
		printf("cd: too many arguments\n");
	}
	else if (code == 2)
	{
		printf("cd: -%c: invalid option\n", cmd[1][1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
	}
	else if (code == 3)
	{
		printf("cd: %s: No such file or directory\n", cmd[1]);
	}
	else if (code == 4)
	{
		printf("%s: HOME not set\n", cmd[1]);
	}
	ft_exst(1);
	return (1);
}

char	*ft_get_pwd(char *name)
{
	t_list	*tmp;

	tmp = g_glv.env;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (tmp->value);
		tmp = tmp->link;
	}
	return (NULL);
}

int	ft_case_home2(char **cmd)
{
	char	*tmp;
	char	*str1;
	char	*subarray;

	subarray = &cmd[1][1];
	tmp = ft_get_pwd("HOME");
	str1 = ft_strjoin(tmp, subarray);
	if (access(str1, F_OK) == 0)
	{
		chdir(str1);
		free(str1);
		return (0);
	}
	else
	{
		printf("cd: no such file or directory: %s\n", str1);
		free(str1);
		ft_exst(1);
		return (1);
	}
	return (1);
}

int	ft_case_home1(char **cmd)
{
	int	ret;

	if (access(ft_get_pwd("HOME"), F_OK) == 0)
	{
		ret = ft_case_home2(cmd);
		return (ret);
	}
	else
	{
		ft_error_cd(cmd, 4);
		return (1);
	}
	return (0);
}

int	ft_case_home(char **cmd)
{
	if (access(ft_get_pwd("HOME"), F_OK) == 0)
		chdir(ft_get_pwd("HOME"));
	else
	{
		ft_error_cd(cmd, 4);
		return (1);
	}
	return (0);
}
