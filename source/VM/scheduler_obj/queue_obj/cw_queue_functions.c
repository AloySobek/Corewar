/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 19:46:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_queue *p_queue_instance, t_process *p_root, int level)
{
	if (p_root)
	{
		p_queue_instance->cw_print_content(p_queue_instance, p_root->p_left, level + 1);
		for (int i = 0; i < level; ++i)
			ft_printf("   ");
		ft_printf("%d\n", p_root->id);
		p_queue_instance->cw_print_content(p_queue_instance, p_root->p_right, level + 1);
	}
}

static void			cw_exec_processes(t_queue *p_queue_instance, t_process *p_root)
{
	t_process *p_left;
	t_process *p_right;

	if (p_root)
	{
		p_left = p_root->p_left;
		p_right = p_root->p_right;
		p_queue_instance->cw_exec_processes(p_queue_instance, p_right);
		if (p_root->kill == CW_FALSE)
		{
			p_queue_instance->game_ref->p_process_obj = p_root;
			p_queue_instance->game_ref->p_process_obj->cw_set_command_time(p_queue_instance->game_ref->p_process_obj, p_queue_instance->game_ref->p_arena_obj);
			p_queue_instance->game_ref->p_process_obj->cw_exec_command(p_queue_instance->game_ref->p_process_obj, p_queue_instance->game_ref);
			if (p_queue_instance->game_ref->p_process_obj->nearest_cycle < 50000)
				p_queue_instance->pa_timeline[p_queue_instance->game_ref->p_process_obj->nearest_cycle]->p_root = p_queue_instance->pa_timeline[p_queue_instance->game_ref->p_process_obj->nearest_cycle]->cw_enqueue(p_queue_instance->pa_timeline[p_queue_instance->game_ref->p_process_obj->nearest_cycle], p_queue_instance->pa_timeline[p_queue_instance->game_ref->p_process_obj->nearest_cycle]->p_root, p_queue_instance->game_ref->p_process_obj);
			else
				exit(1);
		}
		else
			p_root->cw_destructor(&p_root);
		p_queue_instance->cw_exec_processes(p_queue_instance, p_left);
	}
}

static t_process	*cw_right_rotate(t_queue *p_queue_instance, t_process *p_process_obj)
{
	t_process		*p_left;

	if (p_process_obj->p_left)
	{
		p_left = p_process_obj->p_left;
		p_process_obj->p_left = p_left->p_right;
		p_left->p_right = p_process_obj;
		p_queue_instance->cw_set_height(p_queue_instance, p_process_obj);
		p_queue_instance->cw_set_height(p_queue_instance, p_left);
		return (p_left);
	}
}

static t_process	*cw_left_rotate(t_queue *p_queue_instance, t_process *p_process_obj)
{
	t_process	*p_right;

	if (p_process_obj->p_right)
	{
		p_right = p_process_obj->p_right;
		p_process_obj->p_right = p_right->p_left;
		p_right->p_left = p_process_obj;
		p_queue_instance->cw_set_height(p_queue_instance, p_process_obj);
		p_queue_instance->cw_set_height(p_queue_instance, p_right);
		return (p_right);
	}
}

static int		cw_get_balance_factor(t_queue *p_queue_instance, t_process *p_process_instance)
{
	if (p_process_instance)
		return (p_queue_instance->cw_get_height(p_queue_instance, p_process_instance->p_right) - p_queue_instance->cw_get_height(p_queue_instance, p_process_instance->p_left));
	else
		return (0);
}

static int		cw_get_height(t_queue *p_queue_instance, t_process *p_process_obj)
{
	return (p_process_obj ? p_process_obj->height : 0);
}

static void		cw_set_height(t_queue *p_queue_instance, t_process *p_process_obj)
{
	t_tmp		left_height;
	t_tmp		right_height;

	left_height = p_queue_instance->cw_get_height(p_queue_instance, p_process_obj->p_left);
	right_height = p_queue_instance->cw_get_height(p_queue_instance, p_process_obj->p_right);
	p_process_obj->height = (left_height > right_height ? left_height : right_height) + 1;
}

static t_process	*cw_balance(t_queue *p_queue_instance, t_process *p_process_obj)
{
	if (p_process_obj)
	{
		p_queue_instance->cw_set_height(p_queue_instance, p_process_obj);
		if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_process_obj) == 2)
		{
			if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_process_obj->p_right) < 0)
				p_process_obj->p_right = p_queue_instance->cw_right_rotate(p_queue_instance, p_process_obj->p_right);
			return (p_queue_instance->cw_left_rotate(p_queue_instance, p_process_obj));
		}
		if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_process_obj) == -2)
		{
			if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_process_obj->p_left) > 0)
				p_process_obj->p_left = p_queue_instance->cw_left_rotate(p_queue_instance, p_process_obj->p_left);
			return (p_queue_instance->cw_right_rotate(p_queue_instance, p_process_obj));
		}
		return (p_process_obj);
	}
}

static t_process	*cw_enqueue(t_queue *p_queue_instance, t_process *p_root, t_process *p_adding_carriage)
{
	if (p_adding_carriage)
	{
		if (p_root)
		{
			if (p_adding_carriage->id < p_root->id)
				p_root->p_left = p_queue_instance->cw_enqueue(p_queue_instance, p_root->p_left, p_adding_carriage);
			else
				p_root->p_right = p_queue_instance->cw_enqueue(p_queue_instance, p_root->p_right, p_adding_carriage);
			return (p_queue_instance->cw_balance(p_queue_instance, p_root));
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
	p_queue_instance->cw_right_rotate = cw_right_rotate;
	p_queue_instance->cw_left_rotate = cw_left_rotate;
	p_queue_instance->cw_set_height = cw_set_height;
	p_queue_instance->cw_get_height = cw_get_height;
	p_queue_instance->cw_enqueue = cw_enqueue;
	p_queue_instance->cw_balance = cw_balance;
	p_queue_instance->cw_get_balance_factor = cw_get_balance_factor;
	p_queue_instance->cw_exec_processes = cw_exec_processes;
}