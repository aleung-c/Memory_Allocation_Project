/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:37:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/11 12:42:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void						free(void *ptr)
{
	t_mem_seg *tmp;

	tmp = (t_mem_seg *)((char *)ptr - sizeof(t_mem_seg));
	tmp->free = 1;
	ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
}
