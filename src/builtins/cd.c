/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:25:41 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 01:59:37 by misrailo         ###   ########.fr       */
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

int	ft_cd_cases(char **cmd, char *str)
{
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		free(str);
		ft_error_cd(cmd, 2);
		return (1);
	}
	else if (cmd[1] && cmd[1][0] == '-')
	{
		chdir(ft_get_pwd("OLDPWD"));
		return (0);
	}
	else if (cmd[1] == NULL || !ft_strncmp(cmd[1], "~", 2))
		return (ft_case_home(cmd));
	else if (!ft_strncmp(cmd[1], "~", 1) && cmd[1][1] != '\0')
		return (ft_case_home1(cmd));
	else if (cmd[1] && cmd[1][0] != '-' && cmd[1][0] != '~'
		&& chdir(cmd[1]) != 0)
	{
		printf("case4\n");
		free(str);
		ft_error_cd(cmd, 3);
		return (1);
	}
	return (0);
}

void	export_pwds(t_data *data, char **str1, char **str2)
{
	char	*replace[3];

	replace[0] = ft_strjoin("OLDPWD=", *str1);
	printf("oldpwd %s\n", replace[0]);
	replace[1] = ft_strjoin("PWD=", *str2);
	printf("newpwd %s\n", replace[1]);
	replace[2] = NULL;
	ft_export(data, replace, 0);
	free(*str1);
	free(*str2);
	free(replace[0]);
	free(replace[2]);
	free(replace[1]);
	ft_exst(0);
}

int	case_one(char **str1, t_data *data)
{
	ft_exst(1);
	free(*str1);
	if (data->groups != 1)
		exit(1);
	return (0);
}

int	ft_cd(t_data *data, char **cmd, int i)
{
	char	*str1;
	char	*str2;

	str1 = getcwd(NULL, 0);
	if (ft_tab_len(cmd) > 2)
	{
		free(str1);
		ft_error_cd(cmd, 1);
		return (1);
	}
	if (access(cmd[1], F_OK) == 0)
	{
		printf("case0\n");
		chdir(cmd[1]);
	}
	else
		i = ft_cd_cases(cmd, str1);
	if (i == 1)
	{
		if (!case_one(&str1, data))
			return (0);
	}
	str2 = getcwd(NULL, 0);
	export_pwds(data, &str1, &str2);
	return (0);
}
