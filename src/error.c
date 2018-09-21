/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:59:00 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/21 12:40:22 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	invalid_cmd(char *cmd)
{
	if (cmd)
	{
		ft_putstr(EXEC_MSG);
		ft_putstr(ERROR_MSG);
		ft_putstr(cmd);
		ft_putendl(ERR_INVALID_CMD);
	}
}

void	help_menu(void)
{
	ft_putendl("\nMessage Digest commands");
	ft_putendl("md5\n");
}