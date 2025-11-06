/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:06:04 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/06 15:24:49 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putvoidnbr(void *n)
{
	int	*nb;

	nb = (int *)n;
	printf("%d\n", *nb);
}

int	main(void)
{
	t_list	*lst = NULL;
	int		n1 = 325;
	int		n2 = 326;
	int		n3 = 327;
	int		n4 = 328;
	int		n5 = 329;

	ft_lstadd_back(&lst, ft_lstnew(&n1));
	ft_lstadd_back(&lst, ft_lstnew(&n2));
	ft_lstadd_back(&lst, ft_lstnew(&n3));
	ft_lstadd_back(&lst, ft_lstnew(&n4));
	ft_lstadd_back(&lst, ft_lstnew(&n5));
	ft_lstiter(lst, &ft_putvoidnbr);
}