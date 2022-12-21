/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:38:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/12/21 22:37:15 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
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
	char		c;
	char		*content;
	int			i;
}				t_lexer;

typedef struct s_data
{
	t_lexer		lexer;
	t_token		*tokens;
	int			tok_nb;
	char		*cmd;
	char		**cmd_tab;
	int			env_f;
	int			cmd_n;
	int			groups;
	int			d_i;
	t_cmdl		*cmd_l;
	t_cmdl		*cmd_l_free;
	int			cmdl_i;
	int			pid;
	char		**env_str;
	int			freesig;
	int			lg_p;
	int			lg_i;
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

///ENV
void	ft_fill_g_glv(char **env, int num);
int		ft_tab_len(char **env);
char	*ft_get_name(char *env);
char	*ft_get_val(char *env);
void	ft_fill_envstr(t_data *data, char **env);
//PARSING
void	read_line(t_data *data);
int		ft_onlysp(char *s);
int		ft_custom_split(t_data *data);
int		ft_inv_char(char *str);
int		ft_logic_groups(t_data *data, int end, int pipes);
void	ft_save_groups(t_data *data, int grp_nbr, int ii, int start);
int		ft_one_group_function(t_data *data, int grp_nb, int ii);
int		ft_check_if_closed(char c_char, int ii, t_data *data);
void	sg_quotes(t_data *data, int *i, int *j, char *c_char);
void	sg_noquotes(t_data *data, int *i, int *j);
void	sg_savetab(t_data *data, int *i, int grp_nb);
void	sg_cmdtab(t_data *data, int grp_nb, int j, int start);
//PARSING2
int		ft_rules(t_data *data);
int		ft_check_rules(t_data *data);
int		ft_redir_rules(t_data *data, int i);
//DOLLAR
char	*ft_get_first(char *cmd, int end);
char	*ft_get_env(char *cmd, int start, int end);
char	*ft_get_second(char *cmd, int end);
int		ft_read_state(int *sq, int *dq);
int		ft_find_end(char *s, int state, int p);
int		ft_skip_sq(char *cmd, int i, int sq, int dq);
void	ft_q_state(int *sq, int *dq, char c);
//LEXER
int		ft_lexer(t_data *data);
int		ft_dollar_rules(t_data *data);
void	init_lexer(t_data *data);
int		lexer_advance(t_data *data);
void	skip_space(t_data *data);
int		get_next_token(t_data *data, int len);
void	ft_init_tok(t_data *data, int type, char *value);
int		ft_token_r_red(t_data *data);
int		ft_token_l_red(t_data *data);
int		ft_token_filename(t_data *data, int i);
int		ft_separated(t_data *data);
char	*ft_take_arg(t_data *data);
char	*ft_take_cmd(t_data *data);
void	ft_rm_quotes(t_data *data, int i, int j);
char	*ft_rm_quotes2(char *str, int start, int end);
void	puterr(char *cmd);
void	init_pipe(t_data *data, int *cmd);
void	init_cmd(t_data *data, int *cmd, char **tok);
int		ft_filename_error(t_data *data);
void	ft_cmdtok(t_data *data, int qt, int cp);
//FT_EXEC
int		ft_exec(t_data *data);
void	ft_sig_exec(int sig);
void	ft_sig_exec1(int sig);
void	ft_exst(int num);
void	ft_fill_cmdl(t_data *data);
t_cmdl	*ft_init_cmd(void);
char	**ft_get_args(t_data *data, t_cmdl *tmp, int arg, int i);
char	**ft_dum_env_unset(t_data *data);
int		ft_check_redir(t_data *data, int i);
void	ft_errstr(t_data *data);
void	ft_pipes(t_cmdl *cmd);
void	ft_execcmd(t_data *data, char **env);
void	ft_open_pipe(t_cmdl *cmd);
void	ft_close_pipe(t_cmdl *cmd);
int		ft_check_path(t_data *data);
void	ft_exbuiltin(t_data *data);
int		ft_child(t_data *data);
int		exec_cmds(t_data *data);
void	ft_exec_err(t_data *data, int errn, char **env);
int		ft_arrange_path(t_cmdl *cmd, t_data *data);
char	*ft_cur_var(char **sp_path, int i, t_cmdl *cmd);
void	ft_addback_cmdl(t_cmdl **cmd, t_cmdl *new);
int		ft_count_arg(t_data *data, int x);
//REDIRS
void	heredoc(char **redirs, t_cmdl *cmd, int i);
void	echo_contr_sequence(int i);
int		ft_count_red(t_data *data, int x);
void	heredoc1(int file, t_cmdl *cmd);
void	echo_contr_sequence(int c);
void	ft_redirs(t_cmdl *cmd);
void	heredoc1(int file, t_cmdl *cmd);
//FREE MEMORY
void	ft_free_cml1(t_data *data);
void	ft_free_tokens(t_data *data);
void	ft_free_2d(char **str);
void	ft_free_all(t_data *data);
void	ft_dealloc_envstr(t_data *data);
void	ft_dealloc_cmds(t_data *data);
void	ft_free_cmdl(t_data *data);
void	ft_free_envstr(t_data *data);
void	ft_freemem(char **ptr_str, int i);
//UTILS
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strstr(char *str, char *to_find);
int		ft_len_list(t_list *lst);
int		ft_isalnum(int c);
char	*ft_strcat(char *str1, char *str2);
char	*ft_strcat1(char *str1, char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	*ft_memset(void *s, int c, size_t len);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_itoasize(int n);
int		ft_isneg(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_isspace(char c);
size_t	ft_strlen(const char *str);
size_t	ft_strlen_rl(const char *str);
char	*ft_strncpy(char *dst, char *src, size_t len);
void	print_cmd(t_data *data);
void	print_tok(t_data *data);
void	tok_printf(unsigned int tok);
char	*ft_strdup(char *src);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew_last(void);
void	ft_dealloc_env(t_data *data);
void	ft_init_data(t_data *data);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_sig_herd(int sig);
void	rl_replace_line(const char *buff, int n);
void	ft_unset_2env(char *cmd);
void	ft_unset_2envexp(char *cmd);
t_list	*ft_lstnew_addenv(char *name, char *val);
//BUILTINS
int		ft_isbuiltin(t_data *data);
void	ft_echo(t_data *data, char **cmd);
void	ft_pwd(void);
void	ft_export(t_data *data, char **cmd, int c);
int		ft_cd(t_data *data, char **cmd, int i);
void	ft_env(t_data *data, char **cmd);
void	ft_exit(t_data *data, char **cmd);
void	ft_unset(t_data *data, char **cmd);
int		ft_uns_err(char *str);
int		ft_error_cd(char **cmd, int code);
char	*ft_get_pwd(char *name);
int		ft_case_home(char **cmd);
int		ft_case_home1(char **cmd);
void	export_pwds(t_data *data, char **str1, char **str2);
int		ft_check_ravno(char	*str);
int		ft_exp_exist(char *s);
void	ft_print_exp(void);
int		ft_exp_err(char *str);
t_list	*ft_lstnew_exp(char *name, char *val, int num);

#endif
