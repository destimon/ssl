/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:54:34 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/18 15:40:35 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	init_loop(void)
{
	char	**cmd;

	while (1)
	{
		ft_putstr(UI_PROMPT);
		cmd = read_cmd();
		handle_cmd(cmd);
	}
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		init_loop();
	else
	{
		
	}
	return (0);
}
