/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 13:51:32 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/30 16:58:21 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h> //

int main(void)
{
	char *str;
	char *str2;
	char *str3;

	// str2 = ft_malloc(6);
	// str3 = ft_malloc(7);
	printf("Page size = %d\nSize of chunk = %d\n", (int)getpagesize(), (int)sizeof(t_mem_chunk));
	printf("Size of seg = %d\n", (int)sizeof(t_mem_seg));
	// int i = 100;
	char *ptr_test;
	// while (i != 0)
	// {
		ptr_test = ft_malloc(12);
		str = ft_malloc(80);
		str2 = ft_malloc(80);
		str3 = ft_malloc(80);
		ft_strcpy(ptr_test, "abcdefghijklmnopqr");
		printf("%s\n", ptr_test);
		printf("\n");
		// ptr_test = ft_realloc2(ptr_test, 12);
		// printf("%s\n", ptr_test);
		// printf("\n");
		// // ptr_test = ft_realloc2(ptr_test, 25);

		// // str = ft_malloc(45);
		// // printf("test\n");
		printf("\n");
		// ft_free(ptr_test);
		// i--;
	// }
	// str = ft_malloc(4012);
	// ft_strcpy(str, "hellotest");
	// // ft_free(str);
	// str = ft_realloc2(str, 12);
	// ft_strcpy(str, "hellotesteeere");
	// // ft_free(str2);
	// // str3 = ft_malloc(11);
	// str2 = ft_malloc(9);
	// ft_putstr(str);
	// ft_putchar ('\n');

	show_alloc_mem();
	return (0);
}
