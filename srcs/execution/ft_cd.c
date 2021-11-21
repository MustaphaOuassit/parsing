# include "../includes/minishell.h"

void	ft_cd(t_data *data)
{
	//char buf[100];
	if (data->arguments[1] == NULL)
		chdir("/Users/ayafdel");
	else
	{
		if (chdir(data->arguments[1]) == -1)
		{
			ft_putstr_fd("bash: cd: ", 1);
			ft_putstr_fd(data->arguments[1], 1);
			//ft_putstr_fd(" ", 1);
			perror(" ");
		}
		//printf("%s\n",getcwd(buf, sizeof(buf)));
	}
}