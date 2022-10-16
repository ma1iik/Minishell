/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malik <malik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/15 18:51:25 by malik            ###   ########.fr       */
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
	int    groups;
}				t_data;

void 	read_line(t_data *data);
int	    ft_custom_split(t_data *data);
bool    ft_logic_groups(t_data *data, int i, int pipes);
int	    ft_save_groups(t_data *data, int grp_nbr, int ii);

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t len);
int		ft_isspace (char c);
char	*ft_strncpy(char *dst, const char *src, ssize_t len);

#endif
