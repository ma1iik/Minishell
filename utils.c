/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/19 21:52:21 by misrailo         ###   ########.fr       */
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

char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	// printf ("--[%s]--\n", dst);
	// printf ("--[%s]--\n", src);
	// printf ("--[%zu]--\n", len);
	while (src[i] != 0 && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	//printf("hahaha\n");
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
		printf("one zero at the end\n");
		dst[i] = '\0';
	}
	return (dst);
}
void print_cmd(t_data *data)
	{
		printf("---------------------\n");
		printf("|	CMD	     |\n");
		printf("---------------------\n");
		for(int i = 0; i < data->groups; i++)
			printf("[%s]\n", data->cmd_tab[i]);
		printf("---------------------\n");
	}