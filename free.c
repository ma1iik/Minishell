/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:38:27 by ma1iik            #+#    #+#             */
/*   Updated: 2022/10/28 23:45:49 by ma1iik           ###   ########.fr       */
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
		free (data->tokens->value);
		data->tokens->value = NULL;
		i++;
	}
		free(data->tokens);
		data->tokens = NULL;
}