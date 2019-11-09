/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:58:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_obj_container.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	s_queue
{
	t_queue		**pa_timeline;

	t_corewar	*game_ref;

	t_process	*p_root;
	t_process	*p_tree;

	void		(*cw_constructor)				(struct s_queue **);
	t_process	*(*cw_enqueue)					(struct s_queue *, t_process *, t_process *);
	void		(*cw_set_height)				(struct s_queue *, t_process *);
	int			(*cw_get_height)				(struct s_queue *, t_process *);
	int			(*cw_get_balance_factor)		(struct s_queue *, t_process *);
	t_process	*(*cw_right_rotate)				(struct s_queue *, t_process *);
	t_process	*(*cw_left_rotate)				(struct s_queue *, t_process *);
	t_method 	(*cw_exec_processes)			(struct s_queue *, t_process *);
	t_method 	(*cw_exec_processes_with_check)	(struct s_queue *, t_process *);
	t_process	*(*cw_balance)					(struct s_queue *, t_process *);
	void		(*cw_print_content)				(struct s_queue *, t_process *, int);
	void		(*cw_destructor)				(struct s_queue **);
}				t_queue;

void			cw_create_instance_queue(t_queue **pp_queue_obj);
void			cw_queue_functions_linker(t_queue *p_queue_instance);

#endif