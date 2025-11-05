/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:20:51 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/04 14:48:22 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*src_cpy;
	char		*dest_cpy;
	size_t		i;

	i = 0;
	src_cpy = (const char *)src;
	dest_cpy = (char *)dest;
	while (i++ < n)
		dest_cpy[i] = src_cpy[i];
	return (dest);
}
