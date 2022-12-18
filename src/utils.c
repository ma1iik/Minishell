/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 12:15:58 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		i++;
		ptr++;
	}
	return (s);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f')
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

char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != 0 && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < len)
	{
		while (i < len)
		{
			dst[i] = '\0';
			i++;
		}
	}
	else
	{
		dst[i] = '\0';
	}
	return (dst);
}

void	tok_printf(unsigned int tok)
{
	if (tok == 1)
		printf("R_RED");
	else if (tok == 2)
		printf("L_RED");
	else if (tok == 3)
		printf("DR_RED");
	else if (tok == 4)
		printf("DL_RED");
	else if (tok == 5)
		printf("FILE_NAME");
	else if (tok == 6)
		printf("DOLLAR");
	else if (tok == 7)
		printf("CMD");
	else if (tok == 8)
		printf("ARG");
	else if (tok == 9)
		printf("PIPE");
	printf("\n");
	return ;
}
