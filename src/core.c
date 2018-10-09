/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:46:38 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/27 15:17:34 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void		parse_body(t_query *qu, char **parts, int *input, int *i)
{
	if (ft_strequ(parts[*i], "-q"))
		qu->flags |= Q_OPT;
	else if (ft_strequ(parts[*i], "-r"))
		qu->flags |= R_OPT;
	else if (ft_strequ(parts[*i], "-p"))
	{
		*(input) = 0;
		encrypt_input(qu, 1);
	}
	else if (ft_strequ(parts[*i], "-s"))
	{
		*(input) = 0;
		encrypt_arg(qu, &parts[*i], i);
	}
	else
		illegal_moves(parts[*i] + 1, qu->cmd, CMDERR_ILLEGAL);
}

static void		main_encryption(t_query *qu, char **av, int i, int input)
{
	int fd;

	if (input && !av[i])
		encrypt_input(qu, 0);
	else
	{
		while (av[i])
		{
			fd = open(av[i], O_RDONLY);
			if (fd == -1)
				throw_error(av[i], qu->cmd);
			else
				encrypt_file(qu, av[i], fd);
			i++;
		}
	}
}

static int		parse_input_string(t_query *qu, char **parts, int *input)
{
	int	i;

	i = 0;
	qu->flags = 0;
	while (parts[i])
	{
		if (!(parts[i][0] && parts[i][0] == '-' && parts[i][1]))
			break ;
		parse_body(qu, parts, input, &i);
		i++;
	}
	return (i);
}

void			cmd_entrypoint(t_query *qu, char **args)
{
	int input;
	int i;

	i = 0;
	input = 1;
	while (qu->cmd < CMDS)
	{
		if (ft_strequ(args[1], g_cmd[qu->cmd].cmdname))
		{
			if (ft_elems(args) == 1)
				encrypt_input(qu, 0);
			else
			{
				i = parse_input_string(qu, &args[2], &input);
				main_encryption(qu, &args[2], i, input);
			}
			exit(0);
		}
		qu->cmd++;
	}
	if (qu->cmd >= CMDS)
		invalid_cmd(args[1]);
}
