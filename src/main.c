#include "../inc/ft_ssl.h"

t_commands	g_cmd[] = {
	{"md5", "MD5 Message Digest", &md5_printkey},
	{"sha256", "SHA256 Message Digest", &sha256_printkey}
};

static t_query		*init_query(void)
{
	t_query			*qu;

	qu = (t_query*)malloc(sizeof(t_query));
	if (qu)
	{
		qu->cmd = 0;
		qu->flags = 0;
		return (qu);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_query *qu;

	if (argc > 1)
		qu = init_query();
		if (qu)
			cmd_entrypoint(qu, argv);
	else
		show_usage();
	return (0);
}
