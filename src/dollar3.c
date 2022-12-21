/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:32:13 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/18 16:20:14 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_combine_str(char *s1, char *s2, char *s3)
{
	char	*dest;
	char	*tmp;

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
		return (ft_strdup(s2));
	else if (!s1 && !s2 && s3)
		return (ft_strdup(s3));
	else if (s1 && !s2 && !s3)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_replace_d(int state, int end, t_data *data)
{
	char	*first;
	char	*env;
	char	*second;
	char	*ret;

	(void)state;
	first = ft_get_first(data->cmd, data->d_i);
	env = ft_get_env(data->cmd, data->d_i + 1, end);
	second = ft_get_second(data->cmd, end);
	if (!first && !env && !second)
		return (NULL);
	ret = ft_combine_str(first, env, second);
	free(first);
	free(env);
	free(second);
	return (ret);
}

int	ft_env_change(t_data *data, int *sq, int *dq)
{
	char	*new_cmd;
	int		state;
	int		end;

	new_cmd = NULL;
	state = ft_read_state(sq, dq);
	end = ft_find_end(data->cmd, state, data->d_i + 1);
	if (state)
		new_cmd = ft_replace_d(state, end, data);
	if (!new_cmd)
		return (0);
	free(data->cmd);
	data->cmd = ft_strdup(new_cmd);
	free(new_cmd);
	return (1);
}

int	ft_dollar_skip(char *s, int i)
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

int	ft_dollar_rules(t_data *data)
{
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	while (data->cmd[data->d_i])
	{
		data->d_i = ft_skip_sq(data->cmd, data->d_i, sq, dq);
		if (data->cmd[data->d_i] == '"' || data->cmd[data->d_i] == '\'')
			ft_q_state(&sq, &dq, data->cmd[data->d_i]);
		else if (data->cmd[data->d_i] == '$' && data->cmd[data->d_i + 1]
			&& (ft_isalpha(data->cmd[data->d_i + 1])
				|| data->cmd[data->d_i + 1] == '?'))
		{
			if (!ft_env_change(data, &sq, &dq))
				return (0);
		}
		if (data->cmd[data->d_i] && data->cmd[data->d_i] == '$')
			data->d_i = ft_dollar_skip(data->cmd, data->d_i);
		else if (data->cmd[data->d_i] != '\0')
			data->d_i++;
	}
	return (1);
}
