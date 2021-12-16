/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:43:35 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 23:19:18 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token(char *cmd, int *start, t_envp *envp_list)
{
	int		len;
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	len = len_token(cmd, *start);
	if (len == -1)
	{
		*start = -1;
		return (NULL);
	}
	token = (char *)malloc(sizeof(char) * (len + 1));
	free_in_parcer(&envp_list->allocation, token, NULL);
	token[len] = '\0';
	while (i < len)
	{
		token[i] = cmd[*start];
		*start = *start + 1;
		i++;
	}
	return (token);
}

int	end_str(char *cmd)
{
	int	i;

	i = (int)ft_strlen(cmd) - 1;
	if (i < 0)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			break ;
		i--;
	}
	return (i);
}

int	multi_couts(int *i, char *cmd, int ele)
{
	*i = *i + 1;
	if (!check_close(cmd, *i, ele))
		return (1);
	while (cmd[*i])
	{
		if (cmd[*i] == ele)
		{
			*i = *i + 1;
			break ;
		}
		*i = *i + 1;
	}
	return (0);
}

int	first_pipe(char *cmd, int start)
{
	if (cmd[start] == '|' && cmd[start + 1] != '|')
	{
		write(1, "minishell: syntax error near unexpected token `|'\n", 50);
		return (1);
	}
	if (cmd[start] == '|' && cmd[start + 1] == '|')
	{
		write(1, "minishell: syntax error near unexpected token `||'\n", 51);
		return (1);
	}
	return (0);
}

int	middle_pipe(char *cmd, int *i)
{
	char	*str;

	str = "minishell: syntax error near unexpected token `|'\n";
	if (cmd[*i] == '|')
	{
		*i = *i + 1;
		while (cmd[*i])
		{
			if (cmd[*i] == ' ')
				*i = *i + 1;
			else if (cmd[*i] == '|')
			{
				write(1, str, 51);
				return (1);
			}
			else
				break ;
		}
		*i = *i - 1;
	}
	return (0);
}
