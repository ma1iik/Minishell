/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/21 22:01:11 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tab_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp_lst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	tmp_lst = *lst;
	while (tmp_lst->link)
		tmp_lst = tmp_lst->link;
	tmp_lst->link = new;
	while (new->link)
		new = new->link;
	new->link = 0;
	return ;
}

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	(void)content;
	new = ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->link = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> link)
		lst = lst -> link;
	return (lst);
}

int	ft_len_list(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->link;
		len++;
	}
	return (len);
}
