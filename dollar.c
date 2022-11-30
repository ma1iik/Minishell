/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 02:24:32 by ma1iik            #+#    #+#             */
/*   Updated: 2022/11/25 21:34:36 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_skip_sq(char *cmd, int i, int sq, int dq)
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
	//if (c == '\'' && dq)
	if (c == '"' && sq && dq)
	{
		sq = 0;
		*dq = 0;
	}
	else if (c == '"')
		*dq = !dq;
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

int	ft_find_end(char *str, int state, int start)
{
	if (state == 1)
	{
		while (str[start] && (ft_isalnum(str[start]) || str[start] == '_' || str[start] == '@')
			&& str[start] != ' ' && str[start] != '$')
			start++;
	}
	if (state == 2)
	{
		while (str[start] && (ft_isalnum(str[start]) || str[start] == '_' || str[start] == '@')
			&& str[start] != ' ' && str[start] != '$' && str[start] != '"')
			start++;
	}
	if (state == 3)
	{
		while (str[start] && (ft_isalnum(str[start]) || str[start] == '_' || str[start] == '@')
			&& str[start] != ' ' && str[start] != '$' && str[start] != '\'')
			start++;
	}
	if (str[start] == '?')
		return (start + 1);
	return (start);
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

char	*ft_get_second(char *cmd, int end)
{
	char	*ret;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(cmd);
	if (!cmd || end == len)
		return (NULL);
	ret = ft_calloc(sizeof(char *), ft_strlen(cmd) - end + 1);
	if (!ret)
		return (NULL);
	while (cmd[end + j])
	{
		ret[j] = cmd[end + j];
		j++;
	}
	return (ret);
}

char	*ft_get_env(t_data *data, char *cmd, int start, int end)
{
	int		j;
	char	*compare;
	t_list	*tmp;
	char 	*val;
	
	(void)data;
	val = NULL;
	j = 0;
	tmp = glv.env;
	compare = ft_calloc(sizeof(char), end - start + 1);
	if (!compare)
		return (0);
	while (start < end)
		compare[j++] = cmd[start++];
	compare[j] = '\0';
	while (tmp != NULL)
	{
		if (ft_strcmp(compare, tmp->name) == 0)
		{
			val = ft_strdup(tmp->value);
			free(compare);
			return (val);
		}
		tmp = tmp->link;
	}
	free(compare);
	return (NULL);
}

void	ft_free_3(char*s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

char	*ft_dollar_errors(char *s1, char *s2, char *s3)
{
	if (!s1)
		return (ft_strcat(s2, s3));
	else if (!s3)
		return (ft_strcat(s1, s2));
	return (NULL);
}

char	*ft_combine_str(char *s1, char *s2, char *s3)
{
	char	*dest;
	char	*tmp;

	//len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	//dest = ft_calloc(sizeof(char), len + 1);
	if (s1 && s2 && s3)
	{
		tmp = ft_strcat(s1, s2);
		dest = ft_strcat(tmp, s3);
		free (tmp);
		return (dest);
	}
	else if (!s1 && s2 && s3)
		return (ft_strcat(s2, s3));
	else if (s1 && !s2 && s3)
		return (ft_strcat(s1, s3));
	else if (s1 && s2 && !s3)
		return (ft_strcat(s1, s2));
	else if (!s1 && s2 && !s3)
		return (s2);
	else if (!s1 && !s2 && s3)
		return (s3);
	else if (s1 && !s2 && !s3)
		return (s1);
	return (NULL);
}

char	*ft_replace_d(int state, int end, t_data *data)
{
	char	*first;
	char 	*env;
	char	*second;
	char	*ret;

	(void)state;
	first = ft_get_first(data->cmd, data->dollar_i);
	env = ft_get_env(data, data->cmd, data->dollar_i + 1, end);
	second = ft_get_second(data->cmd, end);
	if (!first && !env && !second)
		return (NULL);
	ret = ft_strdup(ft_combine_str(first, env, second));
	ft_free_3(first, env, second);
	return (ret);
}

int	ft_env_change(t_data *data, int *sq, int *dq)
{
	char	*new_cmd;
	int		state;
	int		end;

	state = ft_read_state(sq, dq);
	end = ft_find_end(data->cmd, state, data->dollar_i + 1);
	if (state)
		new_cmd = ft_replace_d(state, end, data);
	if (!new_cmd)
		return (0);
	free(data->cmd);
	data->cmd = ft_strdup(new_cmd);
	free(new_cmd);
	return (1);
}

int ft_dollar_skip(char *s, int i)
{
	if (s[i] == '$')
	{
		if (s[i + 1] == '\0')
			return (i + 1);
		if (s[i + 1] == '"')
			return (i + 1);
		if (s[i + 1] == '$')
			return (i + 2);
		if (s[i + 1] == ' ')
			return (i + 2);
		if (!ft_isalpha(s[i + 1]))
			return (i + 2);
	}
	return (i);
}

int	ft_dollar_rules(t_data *data, int sq, int dq)
{
	while (data->cmd[data->dollar_i])
	{
		data->dollar_i = ft_skip_sq(data->cmd, data->dollar_i, sq, dq);
		if (data->cmd[data->dollar_i] == '"' || data->cmd[data->dollar_i] == '\'')
			ft_q_state(&sq, &dq, data->cmd[data->dollar_i]);
		else if (data->cmd[data->dollar_i] == '$' && data->cmd[data->dollar_i + 1]
			&& (ft_isalpha(data->cmd[data->dollar_i + 1]) || data->cmd[data->dollar_i] == '?'))
		{
			if (!ft_env_change(data, &sq, &dq))
				return (0);
		}
		if (data->cmd[data->dollar_i] && data->cmd[data->dollar_i] == '$')
			data->dollar_i = ft_dollar_skip(data->cmd, data->dollar_i);
		else if (data->cmd[data->dollar_i] != '\0')
			data->dollar_i++;
	}
	return (1);
}