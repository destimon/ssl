/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:11:37 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/10 15:11:39 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlench(const char *s, char ch)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && s[i] != ch)
		i++;
	return (i);
}