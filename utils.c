/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:15 by misrailo          #+#    #+#             */
/*   Updated: 2022/11/30 21:47:02 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		i++;
		ptr++;
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

void	tok_printf(unsigned int tok)
{
	if (tok == 1)
		printf("R_RED");
	else if (tok == 2)
		printf("L_RED");
	else if (tok == 3)
		printf("DR_RED");
	else if (tok == 4)
		printf("DL_RED");
	else if (tok == 5)
		printf("FILE_NAME");
	else if (tok == 6)
		printf("DOLLAR");
	else if (tok == 7)
		printf("CMD");
	else if (tok == 8)
		printf("ARG");
	else if (tok == 9)
		printf("PIPE");
	printf("\n");
	return ;
}

void print_tok(t_data *data)
	{
		printf("---------------------\n");
		printf("|	TOKENS	     |\n");
		printf("---------------------\n");
		for(int i = 0; i < data->tok_nb; i++)
		{
			printf("[%s]\n", data->tokens[i].value);
			tok_printf(data->tokens[i].e_type);
		printf("---------------------\n");
		}
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

void	ft_fill_env(t_data *data, char **env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = data->env;
	while (env[i])
	{
		tmp->name = ft_get_name(env[i]);
		tmp->value = ft_get_val(env[i]);
		i++;
		tmp = tmp->link;
	}
	tmp->name = ft_get_name("?");
}

void	ft_fill_glv(char **env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = glv.env;
	while (env[i])
	{
		tmp->name = ft_get_name(env[i]);
		tmp->value = ft_get_val(env[i]);
		i++;
		tmp = tmp->link;
	}
	tmp->name = ft_get_name("?");
}

void	ft_fill_envstr(t_data *data, char **env)
{
	int		len;
	int		i;

	len = ft_tab_len(env);
	data->env_str = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	while (i < len)
	{
		data->env_str[i] = ft_strdup(env[i]);
		i++;
	}
	data->env_str[i] = ft_strdup("?=0");
}

void	ft_create_env(t_data *data, char **env)
{
	int		len;
	int		i;
	data->env = ft_calloc(sizeof(t_list), 1);
	
	i = 0;
	len = ft_tab_len(env);
	while (i <= len)
	{
		ft_lstadd_back(&data->env, ft_lstnew(env[i]));
		i++;
	}
	//ft_lstadd_back(&data->env, ft_lstnew_last());
	ft_fill_env(data, env);
	ft_fill_envstr(data, env);
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

	(void)content;
	new = ft_calloc(sizeof(t_list), 1);
	if (!content)
		return (NULL);
	if (!new)
		return (NULL);
	new->name = NULL; //ft_get_name(content);
	new->value = NULL; //ft_get_val(content);
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

char	*ft_strcat1(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (0);
	dest = ft_calloc(sizeof(char), ft_strlen(str1) + ft_strlen(str2) + 1);
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

void	ft_exit_st(int x)
{
	t_list	*tmp;

	tmp = glv.env;
	while (ft_strcmp(tmp->name, "?") != 0)
		tmp = tmp->link;
	if (ft_strcmp(tmp->name, "?") == 0)
	{
		free (tmp->name);
		tmp->name = ft_strdup(ft_itoa(x));
	}
}

void	ft_free_2d(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	a;
	unsigned int	b;
	char			*newstr;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1[a])
	{
		newstr[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		newstr[a + b] = s2[b];
		b++;
	}
	newstr[a + b] = '\0';
	return (newstr);
}

int	ft_isbuiltin(t_data *data)
{
	if (!ft_strcmp(data->cmd_l->cmd[0], "pwd")
		|| !ft_strcmp(data->cmd_l->cmd[0], "env")
		|| !ft_strcmp(data->cmd_l->cmd[0], "cd")
		|| !ft_strcmp(data->cmd_l->cmd[0], "echo")
		|| !ft_strcmp(data->cmd_l->cmd[0], "export")
		|| !ft_strcmp(data->cmd_l->cmd[0], "unset"))
		return (1);
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
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
	word = malloc(sizeof(char) * (i + 1));
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

void	ft_freemem(char **ptr_str, int i)
{
	while (i > 0)
	{
		free(ptr_str[i - 1]);
		i--;
	}
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
	ptr_str = malloc(sizeof(char *) * (words + 1));
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
	ptr_str[i] = 0;
	return (ptr_str);
}