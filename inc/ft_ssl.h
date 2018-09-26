#ifndef FT_SSL_H
# define FT_SSL_H

/*	
**		==dcherend's personal guard<<
**		||
**		||
**		\/
**      ___       ___
**     [ШО?] /~\ [ШО?] Be wary before changing anything
**     |ooo|.\_/.|ooo| in this header, brah.
**     |888||   ||888|
**    /|888||   ||888|\
**  /_,|###||___||###|._\
** /~\  ~~~ /[_]\ ~~~  /~\
**(O_O) /~~[_____]~~\ (O_O)
**     (  |       |  )
**    [~` ]       [ '~]
**    |~~|         |~~| 
**    |  |         |  |
**   _<\/>_       _<\/>_
**  /_====_\     /_====_\
*/

# include "../lib/libft/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdint.h>

/*
** Command options.
*/
# define Q_OPT				1
# define R_OPT				2
# define P_OPT				4

/*
**  Algorithm variables.
*/
# define VAR_A				0x67452301
# define VAR_B				0xefcdab89
# define VAR_C				0x98badcfe
# define VAR_D				0x10325476

# define A					0
# define B					1
# define C					2
# define D					3
# define E 					4
# define F 					5
# define G 					6
# define H 					7
# define T1 				8
# define T2 				9

/*
** I/O specs.
*/
# define STACKSIZE 1024
# define CMDS 2

# define CMDERR_ILLEGAL 0
# define CMDERR_ISDIR 1
# define CMDERR_ARGS 2

/*
** Algorithm operations.
*/
# define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))

# define BYTES_32 32
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x) (RROTATE(x,2) ^ RROTATE(x,13) ^ RROTATE(x,22))
# define EP1(x) (RROTATE(x,6) ^ RROTATE(x,11) ^ RROTATE(x,25))
# define SIG0(x) (RROTATE(x,7) ^ RROTATE(x,18) ^ ((x) >> 3))
# define SIG1(x) (RROTATE(x,17) ^ RROTATE(x,19) ^ ((x) >> 10))

typedef struct	s_query
{
	int			cmd;
	int			flags;
}				t_query;


typedef struct	s_package
{
	uint8_t		*key;
	uint8_t		*content;
	int 		content_len;
	int			key_len;
	uint32_t	vars[4];
	uint32_t	varsup[4];
	uint32_t	f;
	uint32_t	g;
	uint32_t	*chunk;
}				t_package;

typedef struct	s_sha256
{
	uint8_t		content[64];
	uint32_t	content_len;
	uint64_t	key_len;
	uint32_t	key[8];
	uint32_t	var[10];
	uint32_t	chunk[64];
}				t_sha256;

typedef struct	s_commands
{
	char		*cmdname;
	char		*desc;
	void		(*function)(char *);
}				t_commands;

extern	t_commands g_cmd[];

/*
**	CORE.
*/

void			cmd_entrypoint(t_query *qu, char **args);

/*
** ENCRYPTING.
*/

char			*read_input(int fd);
void			encrypt_arg(t_query *qu, char **flag_pos, int *i);
void			encrypt_input(t_query *qu, int bol);
void			encrypt_file(t_query *qu, char *file, int fd);

/*
**	MD5_ALGO.
*/

void			md5_printkey(char *content);
void			main_loopbody(t_package *md, int i);
void			md5_encrypt(t_package *md);
t_package		*generate_md5package(uint8_t *content);

/*
**	SHA256_ALGO.
*/

void			sha256_printkey(char *content);
void			sha256_producefinal(t_sha256 *sh);
void			sha256_encrypt(t_sha256 *sh);
void			sha256_chunkprocessing(t_sha256 *sh);

/*
**	OUTPUT.
*/

void			show_usage(void);
void			invalid_cmd(char *cmd);
void			throw_error(char *exp, int cmd_id);
int				is_flag(char *arg);
void			illegal_moves(char *arg, int cmdid, int errid);

#endif
