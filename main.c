/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 13:51:32 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/08 17:29:13 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(void)
{
	// char *str;
	// char *str2;
	// char *str3;

	// str = ft_malloc(8);
	// str2 = ft_malloc(6);
	// str3 = ft_malloc(7);
	printf("size of chunk = %d\n", (int)sizeof(t_mem_chunk));
	printf("size of seg = %d\n", (int)sizeof(t_mem_seg));
	int i = 100;

	while (i != 0)
	{
		ft_malloc(12);
		i--;
	}

	// ft_strcpy(str, "test");
	// ft_strcpy(str2, "test2");
	// ft_strcpy(str3, "test3");
	// ft_putendl(str);
	// ft_putendl(str2);
	// ft_putendl(str3);
	show_alloc_mem();

	return (0);
}