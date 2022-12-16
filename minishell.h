/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/16 21:52:04 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
//# include <readline/ffe.h>
//# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	rl_redisplay(void);
void	rl_replace_line(const char *buffer, int something);
# endif

typedef enum e_type
{
	R_RED = 1,
	L_RED,
	DR_RED,
	DL_RED,
	PIPE,
	FILE_NAME,
	CMD,
	ARG,
	END,
}	t_type;

typedef struct s_cmdl
{
	char			**cmd;
	int				pipe[2];
	int				in;
	int				out;
	int				inf;
	int				outf;
	int				nb_args;
	int				status;
	int				pos;
	int				exit;
	char			**redir;
	struct s_cmdl	*prev;
	struct s_cmdl	*next;
	int				nocmd;
}				t_cmdl;

typedef struct s_token
{
	t_type	e_type;	
	char	*value;
}			t_token;

typedef struct t_list
{
	char			*name;
	char			*value;
	int				flag;
	struct t_list	*link;
}				t_list;

typedef struct s_lexer
{
	char			c;
	char			*content;
	int				i;
}					t_lexer;

typedef struct s_data
{
	t_lexer		lexer;
	t_token		*tokens;
	int			tok_nb;
	char		*cmd;
	char		**cmd_tab;
	int			exit_t;
	int			env_f;
	int			cmd_n;
	int			groups;
	int			d_i;
	t_cmdl		*cmd_l;
	t_cmdl		*cmd_l_free;
	t_list		*env;
	int			cmdl_i;
	int			pid;
	char		**env_str;
	char		**error_str;
	int				freesig;
}				t_data;

typedef struct s_cmd
{
	int			heredoc;
	int			redsig;
	t_list		*env;
	t_list		*env_exp;
	int			env_sig;
}				t_cmd;

t_cmd		g_glv;

//ENV
void			ft_fill_g_glv(char **env, int num);
void			ft_g_glv(char **env, t_data *data);
int				ft_tab_len(char **env);
char			*ft_get_name(char *env);
char			*ft_get_val(char *env);
void			ft_fill_envstr(t_data *data, char **env);

//PARSING
void			read_line(t_data *data);
int				ft_custom_split(t_data *data);
int				ft_logic_groups(t_data *data, int i, int pipes);
int				ft_save_groups(t_data *data, int grp_nbr, int ii);
int				ft_one_group_function(t_data *data, int grp_nb, int ii);
int				ft_check_if_closed(char c_char, int ii, t_data *data);

//PARSING2

int				ft_rules(t_data *data);
int				ft_check_rules(t_data *data);
int				ft_redir_rules(t_data *data, int i);

//LEXER
int				ft_lexer(t_data *data);
int				ft_dollar_rules(t_data *data, int sq, int dq);
void			init_lexer(t_data *data);
int				lexer_advance(t_data *data);
void			skip_space(t_data *data);
int				get_next_token(t_data *data);
void			ft_init_tok(t_data *data, int type, char *value);
int				ft_token_r_red(t_data *data);
int				ft_token_l_red(t_data *data);
int				ft_token_filename(t_data *data);
int				ft_separated(t_data *data);
char			*ft_take_arg(t_data *data);
char			*ft_take_cmd(t_data *data);
void			ft_rm_quotes(t_data *data);
char			*ft_rm_quotes2(char *str, int start, int end);
void			puterr(char *cmd);
//FT_EXEC
int				ft_exec(t_data *data);
void			ft_sig_exec(int sig);
void			ft_sig_exec1(int sig);
void			ft_exst(int num);
void			ft_fill_cmdl(t_data *data);
t_cmdl			*ft_init_cmd(void);
char			**ft_get_args(t_data *data, t_cmdl *tmp);
char			**ft_dum_env_unset(t_data *data);
//REDIRS
void			ft_redirs(t_cmdl *cmd);
void			heredoc(char **redirs, t_cmdl *cmd);
void			echo_contr_sequence(int i);

//FREE MEMORY

void			ft_free_tokens(t_data *data);
void			ft_free_2d(char **str);
void			ft_free_all(t_data *data);
void			ft_dealloc_envstr(t_data *data);
void			ft_dealloc_cmds(t_data *data);
void			ft_free_cmdl(t_data *data);
void			ft_free_envstr(t_data *data);

void			*ft_calloc(size_t count, size_t size);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strstr(char *str, char *to_find);
int				ft_len_list(t_list *lst);
int				ft_isalnum(int c);
char			*ft_strcat(char *str1, char *str2);
char			*ft_strcat1(char *str1, char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
void			*ft_memset(void *s, int c, size_t len);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(char *s1, char *s2);
char			*ft_itoa(int n);
int				ft_isspace(char c);
size_t			ft_strlen(const char *str);
size_t			ft_strlen_rl(const char *str);
char			*ft_strncpy(char *dst, char *src, size_t len);
void			print_cmd(t_data *data);
void			print_tok(t_data *data);
void			tok_printf(unsigned int tok);
char			*ft_strdup(char *src);
t_list			*ft_lstnew(char *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew_last(void);
void			ft_dealloc_env(t_data *data);
void			ft_init_data(t_data *data);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_print_err(t_data *data);
void			ft_sig_herd(int sig);
void			rl_replace_line(const char *buff, int n);
void			ft_unset_2env(char *cmd);


//BUILTINS
int				ft_isbuiltin(t_data *data);
void			ft_echo(t_data *data, char **cmd);
void			ft_pwd(void);
void			ft_export(t_data *data, char **cmd, int c);
int				ft_cd(t_data *data, char **cmd, int i);
void			ft_env(void);
void			ft_exit(t_data *data, char **cmd);
void			ft_unset(t_data *data, char **cmd);

#endif
