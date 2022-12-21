/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:02:59 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:03:01 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_uns_err(char *str)
{
	if (!ft_isalpha(str[0]))
	{
		printf("unset: %s: invalid parameter name\n", str);
		ft_exst(1);
		return (0);
	}
	return (1);
}
