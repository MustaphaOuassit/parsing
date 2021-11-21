/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:50:56 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/06 13:17:16 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	int		i;
	void	*ptr;

	i = 0;
	ptr = malloc(nitems * size);
	if (!ptr)
		return (0);
	while ((int)(nitems * size) > i)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
