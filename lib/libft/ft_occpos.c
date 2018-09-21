/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_occpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:06:51 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/12 13:06:53 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_occpos(char *str, char occ)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == occ)
			return (i);
		i++;
	}
	return (0);
}