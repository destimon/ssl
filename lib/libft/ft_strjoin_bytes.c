/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 17:02:28 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/27 17:03:14 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_bytes(char const *s1, char const *s2, size_t size1,
					size_t size2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_strnew(size1 + size2);
	if (!str)
		return (NULL);
	while (i < (int)size1)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (i < (int)size2)
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	return (str);
}
