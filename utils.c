/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/12 19:59:05 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*dest;
	size_t			i;

	dest = s;
	i = 0;
	while (i < len)
	{
		*dest++ = c;
		i++;
	}
	return (s);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total;

	total = count * size;
	str = malloc(total);
	if (!str)
		return (NULL);
	ft_memset(str, 0, total);
	return (str);
}
