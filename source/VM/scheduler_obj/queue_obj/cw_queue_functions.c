/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 14:11:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_queue *p_queue_instance, t_process *p_root, int level)
{
	if (p_root)
	{
		p_queue_instance->cw_print_content(p_queue_instance,
											p_root->p_left, level + 1);
		for (int i = 0; i < level; ++i)
			ft_printf("   ");
		ft_printf("%d\n", p_root->id);
		p_queue_instance->cw_print_content(p_queue_instance,
											p_root->p_right, level + 1);
	}
}

static void		cw_exec_list_processes(t_queue *p_queue_instance)
{
	;
}

static void		cw_exec_tree_processes(t_queue *p_queue_instance, t_process *p_process_obj)
{
	t_process	*p_left;
	t_process	*p_right;

	if (p_process_obj)
	{
		p_left = p_process_obj->p_left;
		p_right = p_process_obj->p_right;
		p_queue_instance->cw_exec_processes(p_queue_instance, p_right);
		if (p_process_obj->kill == CW_FALSE)
		{
			p_queue_instance->game_ref->p_working_process = p_process_obj;
			p_process_obj->cw_set_command_time(p_process_obj, p_queue_instance->game_ref->p_arena_obj);
			p_process_obj->cw_exec_command(p_process_obj, p_queue_instance->game_ref);
			p_queue_instance->game_ref->p_scheduler->pa_timeline[p_process_obj->nearest_cycle]->p_root =
			p_queue_instance->game_ref->p_scheduler->pa_timeline[p_process_obj->nearest_cycle]->cw_enqueue
			(p_queue_instance->game_ref->p_scheduler->pa_timeline[p_process_obj->nearest_cycle],
			p_queue_instance->game_ref->p_scheduler->pa_timeline[p_process_obj->nearest_cycle]->p_root, p_process_obj);
		}
		else
			p_process_obj->cw_destructor(&p_process_obj);
		p_queue_instance->cw_exec_processes(p_queue_instance, p_left);
	}
}

static t_process	*cw_enqueue(t_queue *p_queue_instance, t_process *p_node, t_process *p_adding_carriage)
{
	if (p_adding_carriage)
	{
		if (p_node)
		{
			if (p_adding_carriage->id < p_node->id)
				p_node->p_left = p_queue_instance->cw_enqueue(p_queue_instance, p_node->p_left, p_adding_carriage);
			else
				p_node->p_right = p_queue_instance->cw_enqueue(p_queue_instance, p_node->p_right, p_adding_carriage);
			return (p_queue_instance->cw_balance(p_queue_instance, p_node));
		}
		else
		{
			p_adding_carriage->p_right = NULL;
			p_adding_carriage->p_left = NULL;
			return (p_queue_instance->cw_balance(p_queue_instance, p_adding_carriage));
		}
	}
	return (NULL);
}

extern void		cw_queue_functions_linker(t_queue *p_queue_instance)
{
	p_queue_instance->cw_print_content = cw_print_content;
	p_queue_instance->cw_enqueue = cw_enqueue;
}