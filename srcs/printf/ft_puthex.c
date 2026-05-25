/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:20:02 by sgil--de          #+#    #+#             */
/*   Updated: 2026/05/25 00:00:00 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(uintptr_t n, int is_upper)
{
	char	*base;
	int		size;

	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	size = 0;
	if (n >= 16)
		size += ft_puthex(n / 16, is_upper);
	size += ft_putchar(base[n % 16]);
	return (size);
}
