#include "ft_ssl.h"

void	main_encryption(t_query *qu, char **av, int i, int input)
{
	int fd;

	if (input && !av[i])
		encrypt_input(qu, 0);
	else
	{
		while (av[i])
		{
			fd = open(av[i], O_RDONLY);
			if (fd == -1)
				throw_error(av[i], qu->cmd);
			else
				encrypt_file(av[i], fd, qu);
			i++;
		}
	}
}

static void	validate_flags(char **parts, t_query *qu)
{
	int	i;
	int input;

	i = 0;
	input = 1;
	qu->flags = 0;
	while (parts[i])
	{
		if (!(parts[i][0] && parts[i][1] && parts[i][0] == '-'))
			break;
		if (ft_strequ(parts[i], "-q"))
			qu->flags |= Q_OPT;
		else if (ft_strequ(parts[i], "-r"))
			qu->flags |= R_OPT;
		else if (ft_strequ(parts[i], "-p"))
		{
			input = 0;
			encrypt_input(qu, 1);
		}
		else if (ft_strequ(parts[i], "-s"))
		{
			input = 0;
			encrypt_arg(qu, &parts[i], &i);
		}
		else
			illegal_moves(parts[i] + 1, qu->cmd, CMDERR_ILLEGAL);
		i++;
	}
	main_encryption(qu, parts, i, input);
}

void	cmd_entrypoint(t_query *qu, char **args)
{
	while (qu->cmd < CMDS)
	{
		if (ft_strequ(args[1], g_cmd[qu->cmd].cmdname))
		{
			if (ft_elems(args) == 1)
				encrypt_input(qu, 0);
			else
				validate_flags(&args[2], qu);
			exit(0);				
		}
		qu->cmd++;
	}
	if (qu->cmd >= CMDS)
		invalid_cmd(args[1]);
}