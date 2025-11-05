/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:34:39 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/04 15:50:50 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BLEU "\033[00;34m"
#define NORMAL "\033[00m"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	ft_print_test_letter(char c, int (*f)(int c), int (*ft)(int c), char *name)
{
	printf(BLEU "Function : %s | Caractere : %c | Reel : %d | FT : %d | Result : %d\n" NORMAL,
		name,
		c,
		f(c),
		ft(c),
		f(c) == ft(c)
	);
}

int	main(void)
{
	char	letter = '/';
	char	phrase[] = "Salut tout le monde";
	char	phrase2[50];

	ft_print_test_letter(letter, &isalpha, &ft_isalpha, "isalpha");
	ft_print_test_letter(letter, &isdigit, &ft_isdigit, "isdigit");
	ft_print_test_letter(letter, &isalnum, &ft_isalnum, "isalnum");
	ft_print_test_letter(letter, &isascii, &ft_isascii, "isascii");
	ft_print_test_letter(letter, &isprint, &ft_isprint, "isprint");

	printf(BLEU "Function : strlen | Phrase : %s | Reel : %lu | FT : %lu | Result : %d\n" NORMAL,
		phrase,
		strlen(phrase),
		ft_strlen(phrase),
		strlen(phrase) == ft_strlen(phrase)
	);

	ft_memcpy(phrase2, phrase, 7);
	phrase2[7] = 0;
	printf("%d\n", phrase2[7]);

	printf("%s\n", phrase);
}