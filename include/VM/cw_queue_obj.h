/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 19:13:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_obj_container.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	s_queue
{
	t_counter	size;

	t_carriage	*p_current_carriage;
	t_carriage	*p_tail;
	t_carriage	*p_head;

	void		(*cw_constructor)	(t_queue **);
	void		(*cw_enqueue)		(t_queue *, t_carriage *);
	void		(*cw_dequeue)		(t_queue *, t_carriage **);
	void		(*cw_count)			(t_queue *, int *);
	void		(*cw_peek)			(t_queue *, t_carriage **);
	void		(*cw_sort)			(t_queue *);
	void		(*cw_reduce_time)	(t_queue *);
	void		(*cw_exec)			(t_queue *);
	void		(*cw_rotate)		(t_queue *);
	void		(*cw_print_content)	(t_queue *);
	void		(*cw_quant_enqueue)	(t_queue *, t_carriage *);
	void		(*cw_destructor)	(t_queue **);
}				t_queue;

void			cw_create_instance_queue(t_queue **pp_queue_obj);
void			cw_queue_functions_linker(t_queue *p_queue_instance);

#endif