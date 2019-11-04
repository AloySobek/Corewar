/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:27:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 17:06:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_SCHEDULER_OBJECT_H
# define CW_SCHEDULER_OBJECT_H

# include "cw_obj_container.h"

# define CW_END_GAME	-777

typedef struct		s_scheduler
{
	t_mark			nearest_cycle;

	t_stack			*p_players_room;
	t_stack			*p_distribution_stack;
	t_queue			*p_execution_queue;
	t_queue			*p_waiting_queue;

	t_method		(*cw_constructor)			(struct s_scheduler **);
	t_method		(*cw_distribute_quantums)	(struct s_scheduler *, t_corewar *);
	t_method		(*cw_relax_waiting_queue)	(struct s_scheduler *, t_corewar *);
	t_getter		(*cw_action_phase)			(struct s_scheduler *);
	t_method		(*cw_queues_init)			(struct s_scheduler *);
	t_method		(*cw_stacks_init)			(struct s_scheduler *);
	t_method		(*cw_kick_players)			(struct s_scheduler *);
	t_method		(*cw_kill_processes)		(struct s_scheduler *);
	t_method		(*cw_destructor)			(struct s_scheduler **);
}					t_scheduler;

void				cw_create_instance_scheduler	(t_scheduler **pp_scheduler_obj);
void				cw_scheduler_functions_linker	(t_scheduler *p_scheduler_instance);

#endif
