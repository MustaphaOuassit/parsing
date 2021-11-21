# include "../includes/minishell.h"

void	ft_pwd()
{
	char buf[100];

	printf("%s\n",getcwd(buf, sizeof(buf)));

}
