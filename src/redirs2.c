/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:10:19 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 10:29:30 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_if(char *infile, t_cmdl *cmd)
{
	cmd->inf = open(infile, O_RDWR, 0644);
	if (cmd->inf == -1)
	{
		printf("%s: no such file or directory\n", infile);
		ft_exst(1);
		exit(1);
	}
	dup2(cmd->inf, cmd->in);
	close(cmd->inf);
	return ;
}

void	open_of(char *outfile, t_cmdl *cmd, int num)
{
	if (num == 1)
		cmd->outf = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->outf = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(cmd->outf, cmd->out);
	close(cmd->outf);
	return ;
}

void	ft_redirs(t_cmdl *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (cmd->redir[i][0] == '<' && cmd->redir[i][1] != '<')
			open_if(cmd->redir[i + 1], cmd);
		else if (cmd->redir[i][0] == '>' && cmd->redir[i][1] != '>')
			open_of(cmd->redir[i + 1], cmd, 1);
		else if (cmd->redir[i][0] == '>' && cmd->redir[i][1] == '>')
			open_of(cmd->redir[i + 1], cmd, 2);
		else if (cmd->redir[i][0] == '<' && cmd->redir[i][1] == '<')
			heredoc(cmd->redir, cmd, 0);
		i += 2;
	}
	return ;
}

void	echo_contr_sequence(int c)
{
	struct termios	conf;

	g_glv.heredoc = 1;
	ioctl(ttyslot(), TIOCGETD, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCGETD, &conf);
}

void	heredoc1(int file, t_cmdl *cmd)
{
	close(file);
	file = open("tmp", O_RDONLY);
	dup2(file, cmd->in);
	close(file);
	unlink("tmp");
}
