/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/12 20:07:13 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char *cmd;
	char **cmd_tab;
	int exit_t;
	
}				t_data;

void	*ft_calloc(size_t count, size_t size);
int	ft_custom_split(char *cmd);
bool ft_logic_groups(char *cmd, int i, int pipes, int groups);
void	*ft_memset(void *s, int c, size_t len);
void 	read_line(t_data *data);
int		ft_isspace (char c);

#endif
