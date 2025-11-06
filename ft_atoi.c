/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:53:33 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/05 17:00:14 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	result;
	int	is_neg;

	result = 0;
	is_neg = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			is_neg = -1;
		s++;
	}
	while (ft_isdigit((int)*s))
	{
		result = (result * 10) + (*s - '0');
		s++;
	}
	return (result * is_neg);
}
