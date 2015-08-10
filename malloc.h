/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 13:41:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/06 11:47:15 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include "./libft/libft.h"

# define TINY (size_t)(getpagesize()) // * 4
# define SMALL (size_t)(getpagesize()) * 4



typedef struct				s_mem_seg // segments dans les zones mmapées.
{
	struct s_mem_seg		*next;
	char					free;
	size_t					size;
}							t_mem_seg;

typedef struct				s_mem_chunk // zone TINY ou SMALL mmapé
{
	t_mem_seg				*first_memseg;
	t_mem_seg				*last_memseg;
	size_t					size_occupied;
	int						nb_segs;
	struct s_mem_chunk		*next;

}							t_mem_chunk;

typedef struct				s_memzone
{
	t_mem_chunk				*tiny;
	t_mem_chunk				*small;
	t_mem_chunk				*big;
}							t_memzone;

extern t_memzone			g_memzone;

/*
** Functions prototypes.
*/

void						ft_free(void *ptr);
void							free_tiny();
void							free_small();
void							free_big(t_mem_seg *tmp, void *ptr);

void							*ft_malloc(size_t size);
char							*allocate_mem(size_t size);

int								check_space(t_mem_chunk *chunk, size_t size, size_t mem_type);
void							allocate_tiny(void);
void							allocate_small(void);
void							allocate_big(size_t size);

char							*search_mem(size_t size);
void							*search_tiny_zone(int size);
void							*search_small_zone(int size);
void						*add_seg_to_chunk(t_mem_chunk *chunk, size_t size_asked, size_t mem_type);
void							*add_first_memseg(t_mem_chunk *chunk, size_t size_asked, size_t mem_type);
void							*add_inner_memseg(t_mem_seg *tmp_segs, t_mem_chunk *chunk, size_t size_asked);
void							*add_outer_memseg(t_mem_seg *tmp_segs, t_mem_chunk *chunk, size_t size_asked, size_t mem_type);
void						*ft_realloc2(void *ptr, size_t size);
void						show_alloc_mem();

#endif