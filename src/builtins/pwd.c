/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:02:36 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:07:59 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
