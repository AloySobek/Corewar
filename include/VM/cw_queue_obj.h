/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 21:25:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_obj_container.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	s_queue
{
	t_corewar	*game_ref;

	t_carriage	*p_root;
	t_carriage	*p_tree;

	void		(*cw_constructor)		(t_queue **);
	t_carriage	*(*cw_enqueue)			(t_queue *, t_carriage *, t_carriage *);
	int			(*cw_get_height)		(t_queue *, t_carriage *);
	int			(*cw_get_balance_factor)(t_queue *, t_carriage *);
	void		(*cw_set_height)		(t_queue *, t_carriage *);
	t_carriage	*(*cw_right_rotate)		(t_queue *, t_carriage *);
	t_carriage	*(*cw_left_rotate)		(t_queue *, t_carriage *);
	t_method 	(*cw_exec_processes)	(struct s_queue *, t_carriage *);
	t_carriage	*(*cw_balance)			(t_queue *, t_carriage *);
	void		(*cw_print_content)		(t_queue *);
	void		(*cw_destructor)		(t_queue **);
}				t_queue;

void			cw_create_instance_queue(t_queue **pp_queue_obj);
void			cw_queue_functions_linker(t_queue *p_queue_instance);

#endif