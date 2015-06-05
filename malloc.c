/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/05 17:20:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *ft_malloc(size_t size)
{
	void *ret;

	ret = allocate_new_mem(size);
	
	return (ret);
}

void *allocate_tiny(size_t size)
{
	void *ret;
	t_mem *tmp;

	ret = (char *)mmap(0, TINY,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED)
	{
		ft_putendl_fd("ERROR - mmap", 2);
		return (NULL);
	}
	// cast pour remplir la zone allouée.
	((t_mem *)ret)->size = size;
	((t_mem *)ret)->ptr = ret + sizeof(t_mem);
	if (g_memzone.tiny == NULL)
	{
		((t_mem *)ret)->next = NULL;
		g_memzone.tiny = ret;
	}
	else
	{
		tmp = g_memzone.tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ret;
	}
	return (((t_mem *)ret)->ptr);
}

void *allocate_new_mem(size_t size)
{
	void *ret;

	ret = NULL;
	if (size < TINY && g_memzone.tiny == NULL)
	{
		ret = allocate_tiny(size);
	}
	else
	{
		ret = search_mem(size);
	}
	return (ret);
}



void *search_mem(size_t size)
{
	if (size)
	{}
	return (NULL);
}