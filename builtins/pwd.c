/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 02:52:14 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/16 20:51:03 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (ret == NULL)
		perror(ret);
	else
	{
		ft_putstr_fd(ret, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	ft_exst(0);
	free(ret);
}