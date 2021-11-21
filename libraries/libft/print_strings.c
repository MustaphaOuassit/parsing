/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:21:08 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/10 16:43:25 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_strings(char	**strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		ft_putstr_fd(strings[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}
