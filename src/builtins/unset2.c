/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:10:53 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 17:13:51 by misrailo         ###   ########.fr       */
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
