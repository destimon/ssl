/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 11:13:20 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/21 17:44:04 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

const uint32_t g_s[] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  
	7, 12, 17, 22, 
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };

const uint32_t g_k[] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

static t_package	*alloc_package(char *content)
{
	t_package		*pckg;

	pckg = (t_package*)malloc(sizeof(t_package));
	if (!content || !pckg)
		return (NULL);
	pckg->content = content;
	pckg->length0 = ft_strlen(content);
	pckg->algo_vars[A] = VAR_A;
	pckg->algo_vars[B] = VAR_B;
	pckg->algo_vars[C] = VAR_C;
	pckg->algo_vars[D] = VAR_D;
	pckg->f = 0;
	pckg->g = 0;
	ft_memcpy(pckg->vars_upper, pckg->algo_vars, 4);
	pckg->hash = NULL;
	pckg->chunk = NULL;
	pckg->length1 = 0;
	return (pckg);
}

static void			bits_padding(t_package **pckg)
{
	if (!pckg || !*pckg)
		return ;
	(*pckg)->length1 = ((*pckg)->length0 * 8) + 1;
	while (1)
	{
		if ((*pckg)->length1 % 512 == 448)
			break;
		(*pckg)->length1++;
	}
	(*pckg)->hash = (uint8_t*)ft_strnew(((*pckg)->length1 + 64) / 8);
	ft_memcpy((*pckg)->hash, (*pckg)->content, (*pckg)->length0);
	(*pckg)->hash[(*pckg)->length0] = (uint8_t)128;
	(*pckg)->length0 *= 8;
	ft_memcpy((*pckg)->hash + (*pckg)->length1 / 8, &(*pckg)->length0, 4);
}

/*
** Fucking magic below...
*/

static void			main_loop_body(t_package *pckg, int i)
{
	if (i >= 0 && i <= 15)
	{
		pckg->f = (pckg->vars_upper[B] & pckg->vars_upper[C]) | 
		((~pckg->vars_upper[B]) & pckg->vars_upper[D]);
		pckg->g = i;
	}
	else if (i >= 16 && i <= 31)
	{
		pckg->f = (pckg->vars_upper[D] & pckg->vars_upper[B]) |
		((~pckg->vars_upper[D]) & pckg->vars_upper[C]);
		pckg->g = (5 * i + 1) % 16;
	}
	else if (i >= 32 && i <= 47)
	{
		pckg->f = pckg->vars_upper[B] ^ pckg->vars_upper[C] ^ 
		pckg->vars_upper[D];
		pckg->g = (3 * i + 5) % 16;
	}
	else if (i >= 48 && i <= 63)
	{
		pckg->f = pckg->vars_upper[C] ^ (pckg->vars_upper[B] 
		| (~pckg->vars_upper[D]));
		pckg->g = (7 * i) % 16;
	}
}

static void			hash_function(t_package *pckg)
{
	int				i;
	int				j;

	j = 0;
	while (j < pckg->length1 / 8)
	{
		ft_memcpy(pckg->algo_vars, pckg->vars_upper, 4);
		pckg->chunk = (uint32_t*)(pckg->hash + j);
		i = 0;
		while (i < 64)
		{
			main_loop_body(pckg, i);
			pckg->f += pckg->vars_upper[A] + g_k[i] + pckg->chunk[pckg->g];
			pckg->vars_upper[A] = pckg->vars_upper[D];
			pckg->vars_upper[D] = pckg->vars_upper[C];
			pckg->vars_upper[C] = pckg->vars_upper[B];
			pckg->vars_upper[B] += LEFT_ROTATE(pckg->f, g_s[i]);
			i++;
		}
		pckg->algo_vars[A] += pckg->vars_upper[A];
		pckg->algo_vars[B] += pckg->vars_upper[B]; 
		pckg->algo_vars[C] += pckg->vars_upper[C];
		pckg->algo_vars[D] += pckg->vars_upper[D];
		j += 64;
	}
	ft_memcpy(pckg->vars_upper, pckg->algo_vars, 4);
}

t_package			*encrypt_content(char *content)
{
	t_package		*pckg;

	if (!content)
		return (NULL);
	pckg = alloc_package(content);
	if (pckg)
	{
		bits_padding(&pckg);
		hash_function(pckg);
		return (pckg);
	}
	return (NULL);
}