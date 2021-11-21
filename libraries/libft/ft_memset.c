/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:19:18 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/06 13:02:57 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	void		*dup;
	size_t		i;

	i = 0;
	dup = str;
	while (i < n)
	{
		((unsigned char *)str)[i] = c;
		i++;
	}
	return (dup);
}
