#include "ft_ssl.h"

static const	uint32_t g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static const	uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void			main_loopbody(t_package *pckg, int i)
{
	if (i < 16)
	{
		pckg->f = (pckg->vars[B] & pckg->vars[C]) | ((~pckg->vars[B]) 
			& pckg->vars[D]);
		pckg->g = i;
	}
	else if (i < 32)
	{
		pckg->f = (pckg->vars[D] & pckg->vars[B]) | ((~pckg->vars[D]) &
		 pckg->vars[C]);
		pckg->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		pckg->f = pckg->vars[B] ^ pckg->vars[C] ^ pckg->vars[D];
		pckg->g = (3 * i + 5) % 16;
	}
	else
	{
		pckg->f = pckg->vars[C] ^ (pckg->vars[B] | (~pckg->vars[D]));
		pckg->g = (7 * i) % 16;
	}
}

void			md5_encrypt(t_package *pckg)
{
	int tmp;
	int i;
	int j;

	j = 0;
	while (j < pckg->key_len)
	{
		pckg->chunk = (uint32_t*)(pckg->key + j);
		ft_memcpy(pckg->vars, pckg->varsup, sizeof(pckg->varsup[0]) * 4);
		i = -1;
		while (++i < 64)
		{
			main_loopbody(pckg, i);
			tmp = pckg->vars[D];
			pckg->vars[D] = pckg->vars[C];
			pckg->vars[C] = pckg->vars[B];
			pckg->vars[B] += LEFT_ROTATE((pckg->vars[A] + pckg->f + 
				g_k[i] + pckg->chunk[pckg->g]), g_s[i]);
			pckg->vars[A] = tmp;
		}
		pckg->varsup[A] += pckg->vars[A];
		pckg->varsup[B] += pckg->vars[B];
		pckg->varsup[C] += pckg->vars[C];
		pckg->varsup[D] += pckg->vars[D];
		j += 64;
	}
}

static t_package	*alloc_package(uint8_t *content)
{
	t_package		*pckg;

	pckg = (t_package*)malloc(sizeof(t_package));
	if (!content || !pckg)
		return (NULL);
	pckg->content = content;
	pckg->content_len = ft_strlen((char*)content);
	pckg->vars[A] = VAR_A;
	pckg->vars[B] = VAR_B;
	pckg->vars[C] = VAR_C;
	pckg->vars[D] = VAR_D;
	ft_memcpy(pckg->varsup, pckg->vars, sizeof(pckg->varsup[0]) * 4);
	pckg->f = 0;
	pckg->g = 0;
	pckg->key = NULL;
	pckg->chunk = NULL;
	pckg->key_len = 0;
	return (pckg);
}

t_package		*generate_md5package(uint8_t *content)
{
	t_package	*pckg;

	pckg = alloc_package(content);
	if (!pckg)
		return (NULL);
	pckg->key_len = pckg->content_len * 8 + 1;
	while (pckg->key_len++)
	{
		if (pckg->key_len % 512 == 448)
			break;
	}
	pckg->key_len /= 8;
	pckg->key = (uint8_t*)ft_memalloc(pckg->key_len + 64);
	ft_memcpy(pckg->key, content, pckg->content_len);
	pckg->key[pckg->content_len] = 128;
	pckg->content_len *= 8;
	ft_memcpy(pckg->key + pckg->key_len, &pckg->content_len, 4);
	md5_encrypt(pckg);
	free(pckg->key);
	return (pckg);
}

void			md5_printkey(char *content)
{
	t_package	*pckg;
	uint8_t	*p;

	pckg = generate_md5package((uint8_t*)content);
	if (pckg)
	{
		p = (uint8_t *)&pckg->varsup[A];
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
		p = (uint8_t *)&pckg->varsup[B];
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
		p = (uint8_t *)&pckg->varsup[C];
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
		p = (uint8_t *)&pckg->varsup[D];
		printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
	}
	free(pckg);
}
