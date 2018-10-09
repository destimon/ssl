/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:28:39 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/27 17:06:32 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void					sha256_producefinal(t_sha256 *sh)
{
	uint32_t pos;

	pos = sh->content_len;
	sh->content[pos++] = 0x80;
	if (pos < 56)
		while (pos < 56)
		{
			sh->content[pos] = 0x00;
			pos++;
		}
	else
	{
		while (pos < 64)
		{
			sh->content[pos] = 0x00;
			pos++;
		}
		sha256_encrypt(sh);
	}
	sh->key_len += sh->content_len * 8;
	pos = -1;
	while (++pos < 8)
		sh->content[63 - pos] = sh->key_len >> (pos * 8);
	sha256_encrypt(sh);
}

void					sha256_chunkprocessing(t_sha256 *sh)
{
	uint32_t i;

	i = -1;
	while (++i < 64)
		sha256vars(sh, i);
	sh->key[A] += sh->var[A];
	sh->key[B] += sh->var[B];
	sh->key[C] += sh->var[C];
	sh->key[D] += sh->var[D];
	sh->key[E] += sh->var[E];
	sh->key[F] += sh->var[F];
	sh->key[G] += sh->var[G];
	sh->key[H] += sh->var[H];
}

void					sha256_encrypt(t_sha256 *sh)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	j = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			sh->chunk[i] = (sh->content[j] << 24) | (sh->content[j + 1] << 16)
			| (sh->content[j + 2] << 8) | (sh->content[j + 3]);
			j += 4;
		}
		else
		{
			sh->chunk[i] = SIG1(sh->chunk[i - 2]) + sh->chunk[i - 7]
			+ SIG0(sh->chunk[i - 15]) + sh->chunk[i - 16];
		}
		i++;
	}
	ft_memcpy(sh->var, sh->key, sizeof(sh->key[0]) * 8);
	sha256_chunkprocessing(sh);
}

static t_sha256			*alloc_package(char *content)
{
	t_sha256			*sh;

	(void)content;
	sh = (t_sha256*)malloc(sizeof(t_sha256));
	if (!sh)
		return (NULL);
	sh->content_len = 0;
	sh->key_len = 0;
	sh->key[A] = 0x6a09e667;
	sh->key[B] = 0xbb67ae85;
	sh->key[C] = 0x3c6ef372;
	sh->key[D] = 0xa54ff53a;
	sh->key[E] = 0x510e527f;
	sh->key[F] = 0x9b05688c;
	sh->key[G] = 0x1f83d9ab;
	sh->key[H] = 0x5be0cd19;
	return (sh);
}

void					sha256_printkey(char *content, int size)
{
	t_sha256			*sh;
	int					i;

	sh = alloc_package(content);
	if (!sh)
		return ;
	i = 0;
	while (i < size)
	{
		sh->content[sh->content_len] = content[i];
		sh->content_len++;
		if (sh->content_len == 64)
		{
			sha256_encrypt(sh);
			sh->key_len += 512;
			sh->content_len = 0;
		}
		i++;
	}
	sha256_producefinal(sh);
	i = -1;
	while (++i < 8)
		printf("%.8x", sh->key[i]);
	free(sh);
	printf("\n");
}
