/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:38:27 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/08 22:29:20 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_data *data)
{
	int		i;

	i = 0;
	if (!data->tokens)
		return ;
	while (i < data->tok_nb)
	{
		free (data->tokens[i].value);
		data->tokens[i].value = NULL;
		i++;
	}
		free(data->tokens);
		data->tokens = NULL;
}