/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malik <malik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:03:06 by misrailo          #+#    #+#             */
/*   Updated: 2022/10/18 15:46:30 by malik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_closed(char c_char, int ii, t_data *data)
{
	char	c;
	int		i;

	c = c_char;
	//printf("%c\n", data->cmd[ii + 1]);
	if ((data->cmd[ii + 1]) == '\0')
	{
        printf ("quotes didnt close\n");
        exit (EXIT_FAILURE);
    }
    else
		i = ii + 1;
	while (data->cmd[i] && data->cmd[i] != c)
		i++;
	if (data->cmd[i] == c)
		return (i);
	else
	{
		printf ("quotes didnt close\n");
		exit (EXIT_FAILURE);
	}
}

bool	ft_logic_groups(t_data *data, int i, int pipes)
{
	while (ft_isspace(data->cmd[i]))
		i++;
	while (data->cmd[i] != '\0')
	{
		if (data->cmd[i] != '|')
		{
			while (data->cmd[i] != '|' && data->cmd[i] != '\0')
			{
				if (data->cmd[i] == '"' || data->cmd[i] == '\'')
				{
					//printf("char is %c\n", data->cmd[i]);
					i = ft_check_if_closed(data->cmd[i], i, data); /*CHANGE*/
                    //printf("char is %c\n", data->cmd[i]);
				}
				i++;
			}
			data->groups += 1;
            printf("logic groups ---> %d\n", data->groups);
		}
		if (data->cmd[i] == '|')
		{
			while (ft_isspace(data->cmd[i + 1]))
				i++;
			if (data->cmd[i + 1] == '|')
				return (0);
			pipes += 1;
			i++;
		}
		if (data->cmd[i + 1] == '\0')
			break ;
	}
	if (pipes + 1 == data->groups)
		return (1);
	return (0);
}

int ft_one_group_function(t_data *data, int grp_nb, int ii)
{
    int i;
    int j;
    int start;
        
    i = ii;
    j = 0;
    while (ft_isspace(data->cmd[i]))
        i++;
    start = i;
    while (data->cmd[i])
    {
        i++;
        j++;
    }
    data->cmd_tab[0] = ft_calloc(j, sizeof(char));
    ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
    printf("logic grouop %d is %s\ngroups exist - %d\n", grp_nb, data->cmd_tab[0], data->groups);
    return (0);
}

int	ft_save_groups(t_data *data, int grp_nbr, int ii)
{
	int	i;
	int	j;
	int	grp_nb;
	int	start;

	grp_nb = grp_nbr + 1;
	i = ii;
	j = 0;
    start = i;
    if (grp_nb == data->groups)
			return (0);
    if (data->groups == 1 || grp_nb + 1 == data->groups)
        ft_one_group_function(data, grp_nb, i);
    else
    {        
        while (data->cmd[i] && grp_nb < data->groups)
        {
            if (data->cmd[i] && data->cmd[i] == '|')
            {
                data->cmd_tab[grp_nb] = ft_calloc(j, sizeof(char));
                ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
                printf("logic grouop %d is %s\ngroups exist - %d\n", grp_nb, data->cmd_tab[grp_nb], data->groups);
                i++;
                ft_save_groups(data, grp_nb, i);
                return (0);
            }
            else if (data->cmd[i] && (data->cmd[i] == '"' || data->cmd[i] == '\''))
            {
                i++;
                while (data->cmd[i] && (data->cmd[i] != '"' && data->cmd[i] != '\''))
                {
                    i++;
                    j++;
                }
                i++;
                j = j + 2;
            }
            else if (data->cmd[i] && data->cmd[i] != '|' && data->cmd[i] != '"' && data->cmd[i] != '\'' )
            {
                while (data->cmd[i] && data->cmd[i] != '|' && data->cmd[i] != '"' && data->cmd[i] != '\'' )
                {
                    i++;
                    j++;
                }
            }
        }
    }
    return(0);
}
        
// 		if (grp_nb == data->groups)
// 			return (0);
// 		while (ft_isspace(data->cmd[i]))
// 			i++;
// 		start = i;
// 		while (data->cmd[i] != '\0')
//         {
//             if (data->cmd[i] == '"' || data->cmd[i] == '\'')
//             {
//                 i = i + 1;
//                 while ((data->cmd[i] != '"' || data->cmd[i] != '\'') && data->cmd[i])
//                 {
//                     j++;
//                     i++;
//                 }
//                 i = i + 1;
//                 j = j + 2;
//             }
//             if (data->cmd[i] != '"' && data->cmd[i] != '\'' && data->cmd[i] != '|')
//             {
//                 while (data->cmd[i] != '"' && data->cmd[i] != '\'' && data->cmd[i] != '|' && data->cmd[i])
//                 {
//                     i++;
//                     j++;
//                 }
//             }
//         }
//         printf("RIGHT HERE\n");
// 		data->cmd_tab[grp_nb] = ft_calloc(j, sizeof(char));
// 		ft_strncpy(data->cmd_tab[grp_nb], &data->cmd[start], j);
// 		printf("logic grouop %d is %s\ngroups exist - %d\n", grp_nb, data->cmd_tab[grp_nb], data->groups);
// 		i++;
// 		j = 0;
// 		grp_nb++;
// 	}
// 	return (0);
// }

int	ft_custom_split(t_data *data)
{
	int	i;

	i = 0;
	data->groups = 0;
	if (!ft_logic_groups(data, 0, 0))
	{
		printf("BAD GROUPS\n");
		exit(EXIT_FAILURE);
	}
	data->cmd_tab = ft_calloc(data->groups, sizeof(char *));
	ft_save_groups(data, -1, 0);
	// {		
	// }
	return (0);
	//should return **char
}

void	read_line(t_data *data)
{
	data->exit_t = 1;
	while (data->exit_t)
	{
		data->cmd = readline("minishell:");
		add_history(data->cmd);
		ft_custom_split(data);
	}
	printf("lol\n");
	data->exit_t = 0;
}

int	main(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	read_line(data);
    //parse_line(data);
    // execute_line();
	return (0);
}
