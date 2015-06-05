/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 15:50:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/05 16:05:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		show_alloc_mem()
{
	t_mem *tmp;

	tmp = g_memzone;
	while (tmp)
	{
		ft_putnbr((int)tmp->ptr);
		ft_putstr("zone mem alloue");
		tmp = tmp->next;
	}
	return ;
}