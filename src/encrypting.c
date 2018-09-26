#include "ft_ssl.h"

char	*read_input(int fd)
{
	char	*str;
	char	buff[STACKSIZE + 1];
	int		ret;
	char	*index;

	str = ft_strnew(0);
	ret = 0;
	while ((ret = read(fd, buff, STACKSIZE)))
	{
		index = str;
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
		free(index);
	}
	return (str);
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

void	encrypt_input(t_query *qu, int flag)
{
	char *str;

	if ((qu->flags & P_OPT))
		str = ft_strnew(0);
	else
	{
		str = read_input(0);
		qu->flags |= P_OPT;
	}
	if (flag)
		ft_putstr(str);
	g_cmd[qu->cmd].function(str);
	ft_putchar('\n');
	free(str);
}

void	encrypt_file(char *filename, int fd, t_query *qu)
{
	char		*str;
	struct stat st;
	char		*command;

	lstat(filename, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		illegal_moves(filename, qu->cmd, CMDERR_ISDIR);
		return ;
	}
	str = read_input(fd);
	command = ft_strdup(g_cmd[qu->cmd].cmdname);
	if (!(qu->flags & Q_OPT) && !(qu->flags & R_OPT))
	{
		ft_putstr(command);
		ft_putstr("(");
		ft_putstr(filename);
		ft_putstr(")= ");
	}
	g_cmd[qu->cmd].function(str);
	if ((qu->flags & R_OPT) && !(qu->flags & Q_OPT))
		ft_putstr(filename);
	ft_putchar('\n');
	free(str);
	free(command);
}
