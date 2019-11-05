/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/05 20:31:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_obj_container.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	s_queue
{
	t_counter	size;

	t_player	*p_head;
	t_carriage	*p_root;

	void		(*cw_constructor)		(t_queue **);
	void		(*cw_enqueue)			(t_queue *, t_carriage *);
	int			(*cw_get_height)		(t_queue *, t_carriage *);
	int			(*cw_get_balance_factor)(t_queue *, t_carriage *);
	void		(*cw_set_height)		(t_queue *);
	void		(*cw_right_rotate)		(t_queue *);
	void		(*cw_left_rotate)		(t_queue *);
	void		(*cw_print_content)		(t_queue *);
	void		(*cw_destructor)		(t_queue **);
}				t_queue;

void			cw_create_instance_queue(t_queue **pp_queue_obj);
void			cw_queue_functions_linker(t_queue *p_queue_instance);

#endif