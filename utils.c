/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/15 06:03:44 by ma1iik           ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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

void	ft_create_env(t_data *data, char **env)
{
	int		len;
	int		i;
	data->env = ft_calloc(sizeof(t_list), 1);
	
	i = 0;
	len = ft_tab_len(env);
	while (i < len)
	{
		ft_lstadd_back(&data->env, ft_lstnew(env[i]));
		i++;
	}
	ft_lstadd_back(&data->env, ft_lstnew_last());
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
	dest = ft_strncpy(dest, &env[i + 1], len);
	return (dest);
}

char	*ft_get_name(char *env)
{
	int		i;
	//int		j;
	char	*dest;

	i = 0;
	//j = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	dest = ft_calloc(sizeof(char), i + 1);
	if (!dest)
		return (0);
	dest = ft_strncpy(dest, env, i);
	// while (j < i)
	// {
	// 	dest[j] = env[j];
	// 	j++;
	// }
	// dest[j] = '\0';
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

	new = ft_calloc(sizeof(t_list), 1);
	if (!content)
		return (NULL);
	if (!new)
		return (NULL);
	new->name = ft_get_name(content);
	new->value = ft_get_val(content);
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

void	ft_dealloc_env(t_data *data)
{
	t_list	*tmp;
	t_list	*aux;

	tmp = data->env;
	while (tmp != NULL)
	{
		aux = tmp;
		tmp = tmp->link;
		free (aux->link);
		free (aux->name);
		free (aux->value);
		free (aux);
	}
}

static int	ft_itoasize(int n)
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

static int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

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
	str = malloc(sizeof(char) * ft_itoasize(n) + 1);
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