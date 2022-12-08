/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:39:48 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 12:41:22 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_data *data, char **cmd)
{
	if (access(cmd[1], F_OK) == 0)
	{
		change_path(data, "OLDPWD");
		chdir(cmd[1]);
		change_path(data, "PWD");
	}
	else if (!path)
		cd_norm(data);
	else
		perror(path);
}
