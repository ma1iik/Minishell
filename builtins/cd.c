/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:25:41 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/15 02:30:34 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_cd_cases(char **cmd, char *str)
{
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		printf("case1\n");
		free (str);
		ft_error_cd(cmd, 2);
		return ;
	}
	else if (cmd[1] && cmd[1][0] == '-')
	{
		printf("case2\n");
		chdir(ft_get_pwd("OLDPWD"));
		return ;
	}
	else if (cmd[1] == NULL || !ft_strncmp(cmd[1], "~", 2))
	{
		if (access("HOME", F_OK))
			chdir(ft_get_pwd("HOME"));
		else
			ft_error_cd(cmd, 4);
		return ;
	}
	else if (cmd[1] && cmd[1][0] != '-' && (cmd[1][0] != '~'
		|| (cmd[1][0] == '~' && cmd[1][1] != '\0')) && chdir(cmd[1]) != 0)
	{
		printf("case4\n");
		free (str);
		ft_error_cd(cmd, 3);
		return ;
	}
	printf("case5\n");
}

int	ft_cd(char **cmd)
{
	char	*str1;
	char	*str2;
	char	*replace[4];

	str1 = getcwd(NULL, 0);
	if (ft_tab_len(cmd) > 2)
	{
		free (str1);
		ft_error_cd(cmd, 1);
		return (1);
	}
	if (access(cmd[1], F_OK) == 0)
	{
		printf("case0\n");
		chdir(cmd[1]);
		
	}
	else
		ft_cd_cases(cmd, str1);
	str2 = getcwd(NULL, 0);
	replace[0] = ft_strjoin("OLDPWD=", str1);
	replace[1] = ft_strjoin("PWD=", str2);
	replace[2] = NULL;
	ft_export(replace, 0);
	free(str1);
	free(str2);
	free(replace[0]);
	free(replace[2]);
	free(replace[1]);
	ft_exst(0);
	return (0);
}