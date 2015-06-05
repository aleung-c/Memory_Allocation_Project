/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 13:41:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/05 17:00:56 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include "./libft/libft.h"

# define TINY 1024
# define SMALL 4096

typedef struct	s_mem
{
	void		*ptr;
	void		*next;
	int			free;
	size_t		size;
}				t_mem;

typedef struct	s_memzone
{
	t_mem		*tiny;
	t_mem		*small;
	t_mem		*big;
}				t_memzone;

t_memzone g_memzone = { NULL, NULL, NULL };


/*
** Functions prototypes.
*/

void		free(void *ptr);

void		*ft_malloc(size_t size);
void			*allocate_new_mem(size_t size);
void			*allocate_tiny(size_t size);

void			*search_mem(size_t size);

void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();


#endif