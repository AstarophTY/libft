/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:38:20 by sgil--de          #+#    #+#             */
/*   Updated: 2026/05/25 00:00:00 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr(void *ptr)
{
	int			size;
	uintptr_t	addr;

	if (!ptr)
		return (ft_putstr("(nil)"));
	addr = (uintptr_t)ptr;
	size = ft_putstr("0x");
	size += ft_puthex(addr, 0);
	return (size);
}
