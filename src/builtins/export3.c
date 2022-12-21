/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidigov <tidigov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:02:28 by tidigov           #+#    #+#             */
/*   Updated: 2022/12/21 23:02:31 by tidigov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_2envexp(char *cmd)
{
	t_list	*tmp;
	char	**str;

	str = ft_split(cmd, '=');
	tmp = g_glv.env_exp;
	while (tmp != NULL && tmp->name != NULL)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
		{
			free(tmp->value);
			if (str[1] != NULL)
				tmp->value = ft_strdup(str[1]);
			else
				tmp->value = NULL;
			tmp->flag = 0;
		}
		tmp = tmp->link;
	}
	ft_free_2d(str);
}

t_list	*ft_lstnew_exp(char *name, char *val, int num)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list), 1);
	if (!name)
		return (NULL);
	if (!new)
		return (NULL);
	if (num == 1)
	{
		new->name = ft_strdup(name);
		new->value = NULL;
		new->flag = 1;
	}
	else if (num == 0)
	{
		new->name = ft_strdup(name);
		if (val != NULL)
			new->value = ft_strdup(val);
		else
			new->value = NULL;
	}
		new->link = NULL;
	return (new);
}
