#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line.h"

typedef struct	s_package
{
	int			algo_vars[4];
	int			vars_upper[4];
	int			f;
	int			g;
	char		*content;
	uint8_t		*hash;
	int			length0;
	int			length1;
	uint32_t	*chunk;
}				t_package;

/*
** Macroses - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/

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

/*
** Output messages.
*/
# define EXEC_MSG			"ft_ssl: "
# define ERROR_MSG			"Error: "

/*
** Errors.
*/ 
# define ERR_INVALID_CMD	" is an invalid command."

/*
** UI.
*/
# define UI_PROMPT			"ft_ssl> "

/*
** Etc.
*/
# define ARRAY_WHITESPACES	"\t\n "
# define CMD_SIZE			1
# define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

/*
** Functions - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/

/*
** CMD.
*/
void			solveout_hash(t_package *pkcg);

/*
** LOOP.
*/
char			**read_cmd();
void			handle_cmd(char **cmd);

/*
** HASH.
*/
t_package		*encrypt_content(char *content);

/*
** ERROR.
*/
void			invalid_cmd(char *cmd);
void			help_menu(void);

#endif
