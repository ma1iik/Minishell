/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils copy 7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 12:21:41 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_wordcount(const char *str, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			words++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (words);
}

char	*ft_words(const char *str, char c)
{
	int		i;
	int		l;
	char	*word;

	i = 0;
	l = 0;
	while (*str == c)
		str++;
	while (str[i] != c && str[i] != '\0')
		i++;
	word = ft_calloc(sizeof(char), (i + 1));
	if (word == NULL)
		return (NULL);
	while (str[l] != c && str[l] != '\0')
	{
		word[l] = str[l];
		l++;
	}
	word[l] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**ptr_str;
	int		words;

	i = 0;
	words = ft_wordcount(s, c);
	if (!s)
		return (NULL);
	ptr_str = ft_calloc(sizeof(char *), (words + 1));
	if (!ptr_str)
		return (NULL);
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		ptr_str[i] = ft_words(s, c);
		if (ptr_str[i] == NULL)
			ft_freemem(ptr_str, i);
		while (*s && *s != c)
			s++;
		i++;
	}
	ptr_str[i] = NULL;
	return (ptr_str);
}
