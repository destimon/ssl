/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 11:12:50 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/21 15:38:07 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void			solveout_hash(t_package *pkcg)
{
	size_t	len;
	uint8_t	*p;

	if (!pkcg)
		return ;
	p = (uint8_t *)&pkcg->algo_vars[A];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&pkcg->algo_vars[B];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&pkcg->algo_vars[C];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&pkcg->algo_vars[D];
	printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
}