/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 10:00:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/06 10:32:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *search_tiny_zone(int size)
{
	t_mem_chunk *tmp;
	void *ret;

	ret = NULL;
	tmp = g_memzone.tiny;
	while (tmp)
	{
		if (check_space(tmp, size, TINY) == 1)
		{
			ret = add_seg_to_chunk(tmp, size, TINY);
			return((char *)ret);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		allocate_tiny();
		ret = search_mem(size);
	}
	return (ret);
}

void *search_small_zone(int size)
{
	t_mem_chunk *tmp;
	void *ret;

	ret = NULL;
	tmp = g_memzone.small;
	while (tmp)
	{
		if (check_space(tmp, size, SMALL) == 1)
		{
			ret = add_seg_to_chunk(tmp, size, SMALL);
			return((char *)ret);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		allocate_small();
		ret = search_mem(size);
	}
	return (ret);
}
