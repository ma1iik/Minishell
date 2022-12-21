/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 02:24:32 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 16:22:26 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skip_sq(char *cmd, int i, int sq, int dq)
{
	char	c;

	if (!cmd)
		return (0);
	if (cmd[i] == '\'' && !sq && !dq)
	{
		c = cmd[i];
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
		if (cmd[i + 1] && cmd[i] == c)
			i++;
	}
	return (i);
}

void	ft_q_state(int *sq, int *dq, char c)
{
	if (c == '"' && *sq && *dq)
	{
		*sq = 0;
		*dq = 0;
	}
	else if (c == '"')
		*dq = !*dq;
}

int	ft_read_state(int *sq, int *dq)
{
	if (!sq && dq)
		return (2);
	else if (sq && dq)
		return (3);
	else if (!sq && !dq)
		return (1);
	else
		return (0);
}

int	ft_find_end(char *s, int state, int p)
{
	if (state == 1)
	{
		while (s[p] && (ft_isalnum(s[p]) || s[p] == '_'
				|| s[p] == '@') && s[p] != ' ' && s[p] != '$')
			p++;
	}
	if (state == 2)
	{
		while (s[p] && (ft_isalnum(s[p]) || s[p] == '_' || s[p] == '@')
			&& s[p] != ' ' && s[p] != '$' && s[p] != '"')
			p++;
	}
	if (state == 3)
	{
		while (s[p] && (ft_isalnum(s[p]) || s[p] == '_'
				|| s[p] == '@') && s[p] != ' ' && s[p] != '$' && s[p] != '\'')
			p++;
	}
	if (s[p] == '?')
		return (p + 1);
	return (p);
}

char	*ft_get_first(char *cmd, int end)
{
	int		i;
	char	*first;

	first = ft_calloc(sizeof(char), end + 1);
	if (!first)
		return (0);
	i = 0;
	if (!cmd || !end)
		return (0);
	while (i < end)
	{
		first[i] = cmd[i];
		i++;
	}
	first[i] = '\0';
	return (first);
}
