/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:18:30 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/21 15:14:53 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include <stdio.h>

char		**read_cmd(void)
{
	char	**cmd;
	char	*line;

	if ((get_next_line(1, &line) > 0))
	{
		if (ft_strlen(line) > 0)
		{
			cmd = ft_strsplit_many(line, ARRAY_WHITESPACES);
			free(line);
			return (cmd);
		}
		free(line);
	}
	return (NULL);
}

char		*readstack_loop(void)
{
	char	*line;
	char	*stack;
	char	*tmp;

	stack = ft_strnew(0);
	while (1)
	{
		get_next_line(0, &line);
		if (line)
		{
			tmp = stack;
			stack = ft_strjoin(stack, line);
			if (tmp)
				free(tmp);
			if (line[0] == (char)0)
				return (stack);
		}
	}
	return (NULL);
}

void		handle_cmd(char **cmd)
{
	t_package	*pkcg;
	char	*content;

	if (cmd)
	{
		if (ft_strequ(cmd[0], "md5"))
		{
			content = ft_strdup(readstack_loop());
			pkcg = encrypt_content(content);
			solveout_hash(pkcg);
			exit(0);
		}
		if (ft_strequ(cmd[0], "exit"))
		{
			exit(0);
		}
		else
		{
			invalid_cmd(cmd[0]);
			help_menu();
		}
		ft_free_twodm(cmd);
	}
}
