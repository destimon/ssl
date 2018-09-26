#include "ft_ssl.h"

void	illegal_moves(char *arg, int cmdid, int errid)
{
	if (errid == CMDERR_ILLEGAL)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(g_cmd[cmdid].cmdname);
		ft_putstr(": illegal iption -- ");
		ft_putendl(arg);
	}
	else if (errid == CMDERR_ARGS)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(g_cmd[cmdid].cmdname);
		ft_putendl(": option requires an argument");
	}
	else if (errid == CMDERR_ISDIR)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(g_cmd[cmdid].cmdname);
		ft_putstr(": ");
		ft_putstr(arg);
		ft_putendl(": is a directory");
	}
	exit(0);
}

void	show_usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
}

void	throw_error(char *exp, int cmd_id)
{
	if (!exp)
		return ;
	ft_putstr("ft_ssl: ");
	ft_putstr(g_cmd[cmd_id].cmdname);
	ft_putstr(": ");
	ft_putstr(exp);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

void	invalid_cmd(char *cmd)
{
	ft_putstr("ft_ssl: Error: ");
	ft_putstr(cmd);
	ft_putendl(" is an invalid command");
	ft_putendl("\nStandard commands:\n");
	ft_putendl("Message Digest commands:\nmd5\nsha256\n");
	ft_putendl("Cipher commands:");
	exit(0);
}

