/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 13:51:32 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/05 16:03:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
	char *str;

	str = ft_malloc(3);
	// str[7] = 'a';
	ft_strcpy(str, "test");

	ft_putendl(str);
	show_alloc_mem();

	return (0);
}