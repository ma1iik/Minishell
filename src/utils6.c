/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils copy 5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 12:19:31 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_makepos(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	makepos;
	int				isneg;
	int				i;
	int				size;

	i = 1;
	makepos = ft_makepos(n);
	isneg = ft_isneg(n);
	size = ft_itoasize(n);
	str = ft_calloc(sizeof(char), ft_itoasize(n) + 1);
	if (!str)
		return (NULL);
	if (makepos == 0)
		str[makepos] = '0';
	while (makepos > 0)
	{	
		str[size - i] = (makepos % 10) + '0';
		makepos /= 10;
		i++;
	}
	if (isneg)
		*str = '-';
	str[size] = '\0';
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strcat(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (0);
	dest = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		dest[i] = str2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
