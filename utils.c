/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/05 21:00:37 by ma1iik           ###   ########.fr       */
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
		//printf("one zero at the end\n");
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

void print_tok(t_data *data)
	{
		printf("---------------------\n");
		printf("|	TOKENS	     |\n");
		printf("---------------------\n");
		for(int i = 0; i < data->tok_nb; i++)
			printf("[%s]\n", data->tokens[i].value);
		printf("---------------------\n");
	}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		l;
	int		i;
	char	*dest;

	l = ft_strlen(src);
	i = 0;
	if (!src)
		return (NULL);
	dest = ft_calloc(sizeof(char),  (l + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_separated(t_data *data)
{
	if (data->lexer.c == ' ' || data->lexer.c == '<' || data->lexer.c == '>' || !data->lexer.c)
		return (1);
	else
		return (0);
}

void	ft_create_env(t_list *head, char **env)
{
	int		len;
	int		i;
	t_list *cur;
	t_list *tmp;
	t_list	node;

	head = &node;
	i = 1;
	len = ft_tab_len(env);
	head->name = ft_get_name(env[0]);
	head->value ft_get_val(env[0]);
	cur = head;
	while (i < len)
	{
		ft_lstadd_back(&head, ft_lstnew(env[i]));
		// tmp = ft_calloc(sizeof(t_list), 1);
		// ft_get_name(tmp, env[i]);
		// ft_get_val(tmp, env[i]);
		// tmp->link = NULL;
		// cur->link = tmp;
		// cur = tmp;
		i++;
	}
		// tmp = ft_calloc(sizeof(t_list), 1);
		// tmp->name = ft_calloc(sizeof(char), 1);
		// tmp->name = "?";
		// tmp->name = ft_calloc(sizeof(char), 1);
		// tmp->value = NULL;
		// tmp->link = NULL;
		// cur->link = tmp;
		// cur = tmp;
}

char	*ft_get_val(char *env)
{
	int		j;
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	if (!env)
	return (NULL);
	while(env[i] && env[i] != '=')
		i++;
	j = i + 1;
	while (env[j] != '\0' && env[j] != '\n')
	{
		len++;
		j++;
	}
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	j = 0;
	i = i + 1;
	while (env[i] != '\0' && env[i] != '\n')
	{
		dest[j] = env[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_get_name(char *env)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	dest = ft_calloc(sizeof(char), i + 1);
	if (!dest)
		return (0);
	while (j < i)
	{
		dest[j] = env[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int ft_tab_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add;

	add = *lst;
	if (!add)
	{
		*lst = new;
		return ;
	}
	add = ft_lstlast(*lst);
	add->link = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->name = content;
	new->value = content;
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