/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/27 23:09:36 by misrailo         ###   ########.fr       */
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

typedef enum e_type
{
	R_REDIR,
	L_REDIR,
	DR_REDIR,
	DL_REDIR,
	FILE_NAME,
	DOLLAR,
	CMD,
	ARG,
}	t_type;

typedef struct s_token
{
	t_type	e_type;	
	char	*value;
}			t_token;

typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*content;
	int				i;
}					t_lexer;

typedef struct s_data
{
	t_lexer lexer;
	t_token token;
	char *cmd;
	char **cmd_tab;
	int exit_t;
	int    groups;
}				t_data;

void 	read_line(t_data *data);
int	    ft_custom_split(t_data *data);
int    ft_logic_groups(t_data *data, int i, int pipes);
int	    ft_save_groups(t_data *data, int grp_nbr, int ii);
int		ft_one_group_function(t_data *data, int grp_nb, int ii);

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t len);
int		ft_isspace (char c);
char	*ft_strncpy(char *dst, char *src, size_t len);
void print_cmd(t_data *data);

#endif
