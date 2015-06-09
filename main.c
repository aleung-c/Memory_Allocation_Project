/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 13:51:32 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/09 16:53:06 by aleung-c         ###   ########.fr       */
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
	printf("Page size = %d\nSize of chunk = %d\n", (int)getpagesize(), (int)sizeof(t_mem_chunk));
	printf("Size of seg = %d\n", (int)sizeof(t_mem_seg));
	int i = 100;

	while (i != 0)
	{
		ft_malloc(1024);
		i--;
	}
	show_alloc_mem();

	return (0);
}