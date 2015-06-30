/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:37:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/30 14:51:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_free(void *ptr)
{
	t_mem_seg *tmp;

	if (!ptr)
		return ;
	tmp = (t_mem_seg *)((char *)ptr - sizeof(t_mem_seg));
	tmp->free = 1;
	if (tmp->size <= TINY)
		g_memzone.tiny->size_occupied -= tmp->size;
	else if (tmp->size <= SMALL)
		g_memzone.small->size_occupied -= tmp->size;
	ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
	ptr = NULL;
}
