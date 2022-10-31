/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/30 15:34:01 by ma1iik           ###   ########.fr       */
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
	R_RED,
	L_RED,
	DR_RED,
	DL_RED,
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
	char			*content;
	int				i;
}					t_lexer;

typedef struct s_data
{
	t_lexer lexer;
	t_token *tokens;
	int		tok_nb;
	char 	*cmd;
	char	**cmd_tab;
	int		exit_t;
	int		groups;
}				t_data;

//PARSING
void		read_line(t_data *data);
int			ft_custom_split(t_data *data);
int			ft_logic_groups(t_data *data, int i, int pipes);
int			ft_save_groups(t_data *data, int grp_nbr, int ii);
int			ft_one_group_function(t_data *data, int grp_nb, int ii);
int			ft_check_if_closed(char c_char, int ii, t_data *data);

//LEXER
int 		init_lexer(t_data *data);
int			lexer_advance(t_data *data);
void		skip_space(t_data *data);
t_token 	*get_next_token(t_data *data);
void		ft_init_tok(t_data *data, int type, char *value);
void		ft_token_r_red (t_data *data, int cmd);
void		ft_token_l_red (t_data *data, int cmd);
void		ft_token_filename(t_data *data);
void		ft_tokenise_rest(t_data *data, int cmd);
int			ft_separated(t_data *data);
char		*ft_take_arg(t_data *data);
char		*ft_take_cmd(t_data *data);

//FREE MEMORY

void	ft_free_tokens(t_data *data);

void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *s, int c, size_t len);
int			ft_isspace (char c);
int			ft_strlen(const char *str);
char		*ft_strncpy(char *dst, char *src, size_t len);
void 		print_cmd(t_data *data);
char		*ft_strdup(char *src);

#endif
