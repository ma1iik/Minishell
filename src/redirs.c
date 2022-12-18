/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:10:19 by ma1iik            #+#    #+#             */
/*   Updated: 2022/12/18 10:30:19 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_hdfile(int *file)
{
	*file = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (*file == -1)
		puterr("");
}

void	writein_hd(int *file, char **s)
{
	write(*file, *s, ft_strlen(*s));
	write(*file, "\n", 1);
	free(*s);
}

void	heredoc(char **r, t_cmdl *cmd, int i)
{
	int		file;
	char	*s;

	signal(SIGINT, ft_sig_herd);
	while (r[i])
	{
		if (r[i][0] == '<' && r[i][1] == '<')
		{
			open_hdfile(&file);
			while (1)
			{
				echo_contr_sequence(0);
				s = readline(">");
				if (!s || !ft_strncmp(s, r[i + 1], (ft_strlen(r[i + 1]) + 1)))
				{
					free(s);
					break ;
				}
				writein_hd(&file, &s);
			}
			g_glv.heredoc = 0;
		}
		i += 2;
	}
	heredoc1(file, cmd);
}
