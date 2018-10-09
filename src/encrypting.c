/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:00:48 by dcherend          #+#    #+#             */
/*   Updated: 2018/09/27 17:41:26 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

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
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	sha256vars(t_sha256 *sh, int i)
{
	sh->var[T1] =
	sh->var[H] + EP1(sh->var[E]) +
	CH(sh->var[E], sh->var[F], sh->var[G]) + g_k[i] + sh->chunk[i];
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

void	encrypt_file(t_query *qu, char *file, int fd)
{
	char		*inp;
	int			size;
	struct stat stats;
	char		*command;

	size = 0;
	lstat(file, &stats);
	if (S_ISDIR(stats.st_mode) || S_ISLNK(stats.st_mode))
	{
		illegal_moves(file, qu->cmd, CMDERR_ISDIR);
		return ;
	}
	inp = read_input(fd, &size);
	command = ft_strdup(g_cmd[qu->cmd].cmdname);
	if (!(qu->flags & Q_OPT) && !(qu->flags & R_OPT))
		file_output(command, file);
	g_cmd[qu->cmd].function(inp, size);
	if ((qu->flags & R_OPT) && !(qu->flags & Q_OPT))
		ft_putendl(file);
	free(inp);
	free(command);
}

void	encrypt_arg(t_query *qu, char **flag_pos, int *i)
{
	char *command;

	(*i)++;
	if (!flag_pos[1])
		illegal_moves(NULL, qu->cmd, CMDERR_ARGS);
	command = ft_strdup(g_cmd[qu->cmd].cmdname);
	if (!(qu->flags & Q_OPT) && !(qu->flags & R_OPT))
	{
		ft_putstr(command);
		ft_putstr("(\"");
		ft_putstr(flag_pos[1]);
		ft_putstr("\")= ");
	}
	g_cmd[qu->cmd].function(flag_pos[1], ft_strlen(flag_pos[1]));
	if ((qu->flags & R_OPT) && !(qu->flags & Q_OPT))
	{
		ft_putstr("\"");
		ft_putstr(flag_pos[1]);
		ft_putendl("\"");
	}
	free(command);
}

char	*read_input(int fd, int *size)
{
	char	*inp;
	int		bytes;
	char	stack[STACKSIZE + 1];
	char	*index;

	bytes = 0;
	inp = ft_strnew(0);
	while ((bytes = read(fd, stack, STACKSIZE)))
	{
		index = inp;
		stack[bytes] = '\0';
		inp = ft_strjoin_bytes(inp, stack, *size, bytes);
		*size += bytes;
		free(index);
	}
	return (inp);
}

void	encrypt_input(t_query *qu, int bol)
{
	int		size;
	char	*inp;

	size = 0;
	if ((qu->flags & P_OPT))
		inp = ft_strnew(0);
	else
	{
		inp = read_input(0, &size);
		qu->flags |= P_OPT;
	}
	if (bol)
		ft_putstr(inp);
	g_cmd[qu->cmd].function(inp, size);
	ft_putchar('\n');
	free(inp);
}
