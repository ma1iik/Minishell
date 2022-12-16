/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 02:41:41 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/17 00:21:22 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	extentions(t_list *prec, t_list *cur)
{
		prec = cur;
		cur = cur->next;
}

t_list	*add_at(t_list *lst, char *str, int pos, int i)
{
	t_list	*prec;
	t_list	*cur;
	t_list	*cell;
	char	*temp_str;

	prec = NULL;
	cur = NULL;
	cell = NULL;
	temp_str = ft_strdup(str);
	prec = lst;
	cur = lst;
	creat_cell(&cell, temp_str);
	if (is_empty_list(lst))
		return (cell);
	if (pos == 0)
	{
		cell->next = lst;
		return (cell);
	}
	while (i++ < pos)
		extentions(prec, cur);
	prec->next = cell;
	cell->next = cur;
	return (lst);
}

char	*ft_getenv(char *env, t_data *data, int i)
{
	t_list	*tmp_lst;

	tmp_lst = data->env;
	while (tmp_lst)
	{
		if (ft_strchr_env(tmp_lst->content, env))
		{
			if (i)
				free(env);
			return (ft_str_chr(tmp_lst->content, '='));
		}
		tmp_lst = tmp_lst->next;
	}
	if (i)
		free(env);
	manager(tmp_lst, 0);
	return (NULL);
}

char	*act(char *dest, char *new_dest_content, char *content_to_add, int i)
{
	if (dest[i])
	{
		i++;
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 1));
	}
	else
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 2));
	manager(new_dest_content, 0);
	return (new_dest_content);
}

char	*act2(char *new_dest_content, char *content_to_add, int i)
{
	int	j;

	j = 0;
	if (content_to_add == NULL)
		new_dest_content[i] = '\0';
	else
	{
		while (content_to_add[j] != '\0')
			new_dest_content[i++] = content_to_add[j++];
		new_dest_content[i] = '\0';
	}
	return (new_dest_content);
}
