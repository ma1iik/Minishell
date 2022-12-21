/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:03:27 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:30 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd_cases(char **cmd)
{
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
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
		ft_error_cd(cmd, 3);
		return (1);
	}
	return (0);
}

void	export_pwds(t_data *data, char **str1, char **str2)
{
	char	*replace[3];

	replace[0] = ft_strjoin("OLDPWD=", *str1);
	replace[1] = ft_strjoin("PWD=", *str2);
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
		chdir(cmd[1]);
	}
	else
		i = ft_cd_cases(cmd);
	if (i == 1)
	{
		if (!case_one(&str1, data))
			return (0);
	}
	str2 = getcwd(NULL, 0);
	export_pwds(data, &str1, &str2);
	return (0);
}
