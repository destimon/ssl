#include "ft_ssl.h"

static const	uint32_t g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void			sha256_producefinal(t_sha256 *sh)
{
	uint32_t pos;

	pos = sh->content_len;
	if (pos < 56)
	{
		sh->content[pos++] = 0x80;
		while (pos < 56)
		{
			sh->content[pos] = 0x00;
			pos++;
		}
	}
	else
	{
		sh->content[pos++] = 0x80;
		while (pos < 64)
		{
			sh->content[pos] = 0x00;
			pos++;
		}
		sha256_encrypt(sh);
		// ft_memset(sh->content, 0, 56); ?????????????????????????
 	}
	sh->key_len += sh->content_len * 8;
	pos = -1;
	while (++pos < 8)
		sh->content[63 - pos] = sh->key_len >> (pos * 8);
	sha256_encrypt(sh);
}

void			sha256_chunkprocessing(t_sha256 *sh)
{
	uint32_t i;

	i = -1;
	while (++i < 64)
	{
		sh->var[T1] =
		sh->var[H] + EP1(sh->var[E]) + CH(sh->var[E], sh->var[F], sh->var[G]) + g_k[i] + sh->chunk[i];
		sh->var[T2] = EP0(sh->var[A]) + MAJ(sh->var[A], sh->var[B], sh->var[C]);
		sh->var[H] = sh->var[G];
		sh->var[G] = sh->var[F];
		sh->var[F] = sh->var[E];
		sh->var[E] = sh->var[D] + sh->var[T1];
		sh->var[D] = sh->var[C];
		sh->var[C] = sh->var[B];
		sh->var[B] = sh->var[A];
		sh->var[A] = sh->var[T1] + sh->var[T2];
	}
	sh->key[A] += sh->var[A];
	sh->key[B] += sh->var[B];
	sh->key[C] += sh->var[C];
	sh->key[D] += sh->var[D];
	sh->key[E] += sh->var[E];
	sh->key[F] += sh->var[F];
	sh->key[G] += sh->var[G];
	sh->key[H] += sh->var[H];
}

void			sha256_encrypt(t_sha256 *sh)
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


static t_sha256		*alloc_package(char *content)
{
	t_sha256		*sh;

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

void			sha256_printkey(char *content)
{
	t_sha256	*sh;
	int			i;

	sh = alloc_package(content);
	if (sh)
	{
		i = 0;
		while (i < (int)ft_strlen(content))
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
	}
	// printf("\n");
}
