//#include<stdio.h>
# include "../includes/minishell.h"

int		is_n(char *str)
{
	int i;

	i = 0;
	
	if (str == NULL)
		return (0);
	if (ft_strlen(str) < 2)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
int		ft_echo(t_data *data)
{
	int i;
	int	n_flag;
	int	*fd;
	int tmp_fd;

	i = 1;
	n_flag = 0;	

	while(is_n(data->arguments[i]))
		i++;
	if (i > 1)
		n_flag = 1;
	fetch_fd(data->redirection, &fd);
	if (fd[1] != 1)
	{
		//printf("fd[1]=%d\n", fd[1]);
		//printf("%d\n", fd[1]);
		tmp_fd = dup(1);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	while (data->arguments[i])
	{
		ft_putstr_fd(data->arguments[i], 1);
		i++;
		if (data->arguments[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		printf("\n");
	dup2(tmp_fd, 1);
	return (0);
}