/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:54:02 by sgil--de          #+#    #+#             */
/*   Updated: 2026/05/25 00:00:00 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		size;

	nb = n;
	size = 0;
	if (nb < 0)
	{
		size += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		size += ft_putnbr(nb / 10);
	size += ft_putchar((nb % 10) + '0');
	return (size);
}

int	ft_putunbr(unsigned int n)
{
	int	size;

	size = 0;
	if (n >= 10)
		size += ft_putunbr(n / 10);
	size += ft_putchar((n % 10) + '0');
	return (size);
}
