/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 12:33:10 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}

t_list	*ft_lstnew_last(void)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->name = ft_strdup("?");
	new->value = ft_strdup("0");
	new->link = NULL;
	return (new);
}

int	ft_itoasize(int n)
{
	int		nbr;
	int		size;

	nbr = n;
	size = 0;
	if (nbr < 0 && nbr > -2147483648)
	{
		size++;
		nbr = -nbr;
	}
	if (nbr == 0)
		return (1);
	else if (nbr == -2147483648)
		return (11);
	while (nbr > 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}
