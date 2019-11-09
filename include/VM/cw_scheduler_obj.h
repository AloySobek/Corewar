/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:27:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:58:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_SCHEDULER_OBJECT_H
# define CW_SCHEDULER_OBJECT_H

# include "cw_obj_container.h"

# define SC_END_GAME			-777
# define SC_MAX_CYCLE_SUPPORT	50000

typedef struct		s_scheduler
{
	t_counter		processes_amount;
	t_counter		players_amount;

	t_player		*p_player_obj;
	t_process		*p_carriage_obj;
	t_queue			*pa_timeline[SC_MAX_CYCLE_SUPPORT];

	t_method		(*cw_constructor)			(struct s_scheduler **);
	t_method		(*cw_insert_process)		(struct s_scheduler *, t_process *, int);
	t_method		(*cw_list_process)			(struct s_scheduler *, t_process *);
	t_method		(*cw_insert_player)			(struct s_scheduler *, t_player *);
	t_method		(*cw_kick_players)			(struct s_scheduler *);
	t_method		(*cw_queues_init)			(struct s_scheduler *, t_corewar *);
	t_method		(*cw_destructor)			(struct s_scheduler **);
}					t_scheduler;

void				cw_create_instance_scheduler	(t_scheduler **pp_scheduler_obj);
void				cw_scheduler_functions_linker	(t_scheduler *p_scheduler_instance);

#endif
