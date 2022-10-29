/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:15:49 by ma1iik            #+#    #+#             */
/*   Updated: 2022/10/29 09:38:36 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_tok(t_data *data, int type, char *value)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = ft_calloc(sizeof(t_token), data->tok_nb + 1);
	if (!tmp)
		return ;
	while (i < data->tok_nb)
	{
		tmp[i].e_type = data->tokens[i].e_type;
		tmp[i].value = ft_strdup(data->tokens[i].value);
		i++;
	}
	tmp[i].e_type = type;
	tmp[i].value = ft_strdup(value);
	if (data->tokens)
		ft_free_tokens(data);
	data->tokens = tmp;
	data->tok_nb++;
}

ft_token_l_red (t_data *data, int cmd)
{
	char	*file;

	if (data->lexer.content[data->lexer.i + 1 == '<'])
	{
		ft_init_tok(data, DL_RED, "<<");
		lexer_advance(data);
	}
	else
		ft_init_tok(data, L_RED, "<");
	lexer_advance(data);
	ft_tocken_filename(data);
	
}

ft_token_r_red (t_data *data, int cmd)
{
	char	*file;

	if (data->lexer.content[data->lexer.i + 1 == '>'])
	{
		ft_init_tok(data, DL_RED, ">>");
		lexer_advance(data);
	}
	else
		ft_init_tok(data, L_RED, ">");
	lexer_advance(data);
	ft_tocken_filename(data);
	
}

void	ft_tocken_filename(t_data *data)
{
	char	*file;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (ft_isspace(data->lexer.c))
		skip_space(data);
	start = data->lexer.i;
	while (!ft_isspace(data->lexer.c) && data->lexer.c != '<' && data->lexer.c != '>')
		lexer_advance(data);
	end = data->lexer.i;
	file = ft_calloc(sizeof(char), (end - start + 1));
	while (start < end)
	{
		file[i] = data->lexer.content[start];
		i++;
		start++;
	}
	file[i] = '\0';
	ft_init_tok(data, FILE_NAME, file);
	free (file);
}