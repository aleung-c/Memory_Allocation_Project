/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/05 15:48:11 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *ft_malloc(size_t size)
{
	void *ret;

	if (g_memzone == NULL)
	{
		ret = allocate_new_mem(size);
	}
	else
	{
		ret = search_mem(size);
	}
	return (ret);
}

void *allocate_tiny(size_t size)
{
	void *ret;
	t_mem memzone;
	t_mem *tmp;

	// mmap;
	ret = mmap(0, TINY,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED)
	{
		ft_putendl_fd("ERROR - mmap", 2);
		return (NULL);
	}
	// remplir structure.
	memzone.ptr = ret + sizeof(t_mem);
	memzone.size = size;
	//ft_memcpy(&ret, &memzone, sizeof(t_mem));
	if (g_memzone == NULL)
		g_memzone = ret;
	else
	{
		tmp = g_memzone;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ret;
	}
	return (memzone.ptr);
}

void *allocate_new_mem(size_t size)
{
	void *ret;

	ret = NULL;
	if (size < TINY)
	{
		ret = allocate_tiny(size);
	}
	return (ret);
}



void *search_mem(size_t size)
{
	if (size)
	{}
	return (NULL);
}