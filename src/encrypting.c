#include "../inc/ft_ssl.h"

void	encrypt_file(t_query *qu, char *file, int fd)
{
	char		*inp;
	struct stat stats;
	char		*command;

	lstat(file, &stats);
	// if ((st.st_mode & S_IFMT) == S_IFDIR)
	if (S_ISDIR(stats.st_mode))
	{
		illegal_moves(file, qu->cmd, CMDERR_ISDIR);
		return ;
	}
	inp = read_input(fd);
	command = ft_strdup(g_cmd[qu->cmd].cmdname);
	if (!(qu->flags & Q_OPT) && !(qu->flags & R_OPT))
	{
		ft_putstr(command);
		ft_putstr("(");
		ft_putstr(file);
		ft_putstr(")= ");
	}
	g_cmd[qu->cmd].function(inp);
	if ((qu->flags & R_OPT) && !(qu->flags & Q_OPT))
		ft_putstr(file);
	ft_putchar('\n');
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
	g_cmd[qu->cmd].function(flag_pos[1]);
	if ((qu->flags & R_OPT) && !(qu->flags & Q_OPT))
	{
		ft_putstr("\"");
		ft_putstr(flag_pos[1]);
		ft_putstr("\"");
	}
	ft_putchar('\n');
	free(command);
}

char	*read_input(int fd)
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
		inp = ft_strjoin(inp, stack);
		free(index);
	}
	return (inp);
}

void	encrypt_input(t_query *qu, int bol)
{
	char *inp;

	if ((qu->flags & P_OPT))
		inp = ft_strnew(0);
	else
	{
		inp = read_input(0);
		qu->flags |= P_OPT;
	}
	if (bol)
		ft_putstr(inp);
	g_cmd[qu->cmd].function(inp);
	ft_putchar('\n');
	free(inp);
}

