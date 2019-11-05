/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/05 20:36:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_queue *p_queue_instance)
{
	int			iter;

	iter = CW_ITERATOR;
	;
}

static void		cw_right_rotate(t_queue *p_queue_instance, t_carriage *p_carriage_obj)
{
	t_carriage	*p_left;

	if (p_queue_instance->p_root && p_queue_instance->p_root->p_left)
	{
		p_left = p_queue_instance->p_root->p_left;
		p_queue_instance->p_root->p_left = p_left->p_right;
		p_left->p_right = p_queue_instance->p_root;
		p_queue_instance->p_root = p_left;
	}
}

static void		cw_left_rotate(t_queue *p_queue_instance, t_carriage *p_carriage_obj)
{
	t_carriage	*p_right;

	if (p_carriage_obj)
	{
		if (p_carriage_obj == p_queue_instance->p_root && p_queue_instance->p_root->p_right)
		{
			p_right = p_queue_instance->p_root->p_right;
			p_queue_instance->p_root->p_right = p_right->p_left;
			p_right->p_left = p_queue_instance->p_root;
			p_queue_instance->p_root = p_right;
		}
		else if (p_carriage_obj->p_right)
		{
			p_right = p_carriage_obj->p_right;
			p_carriage_obj->p_right = p_right->p_left;
			p_right->p_left = p_carriage_obj;
		}
}

static void		cw_get_balance_factor(t_queue *p_queue_instance, t_carriage *p_carriage_obj)
{
	int			balance_factor;

	balance_factor = 0;
	if (p_carriage_obj)
	{
		balance_factor = p_queue_instance->cw_get_height(p_queue_instance, p_carriage_obj->p_right)
		- p_queue_instance->cw_get_height(p_queue_instance, p_carriage_obj->p_left);
	}
	return (balance_factor);
}

static int		cw_get_height(t_queue *p_queue_instance, t_carriage *p_carriage_obj)
{
	return (p_carriage_obj ? p_carriage_obj->height : 0);
}

static void		cw_set_height(t_queue *p_queue_instance)
{
	t_tmp		left_height;
	t_tmp		right_height;

	left_height = p_queue_instance->cw_get_height(p_queue_instance, p_queue_instance->p_root->p_left);
	right_height = p_queue_instance->cw_get_height(p_queue_instance, p_queue_instance->p_root->p_right);
	p_queue_instance->p_root->height = (left_height > right_height ? left_height : right_height) + 1;
}

static void		cw_balance(t_queue *p_queue_instance)
{
	p_queue_instance->cw_set_height(p_queue_instance);
	if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_queue_instance->p_root) == 2)
	{
		if (p_queue_instance->cw_get_balance_factor(p_queue_instance, p_queue_instance->p_root->p_right) < 0)

	}
}

static void		cw_enqueue(t_queue *p_queue_instance, t_carriage *p_adding_carriage)
{
	if (p_adding_carriage)
	{
		if (!p_queue_instance->p_root)
		{
			p_adding_carriage->p_right = NULL;
			p_adding_carriage->p_left = NULL;
			p_queue_instance->p_root = p_adding_carriage;
		}
		else
		{
			;
		}
	}
}

extern void		cw_queue_functions_linker(t_queue *p_queue_instance)
{
	p_queue_instance->cw_print_content = cw_print_content;
	p_queue_instance->cw_right_rotate = cw_right_rotate;
	p_queue_instance->cw_left_rotate = cw_left_rotate;
	p_queue_instance->cw_set_height = cw_set_height;
	p_queue_instance->cw_get_height = cw_get_height;
	p_queue_instance->cw_enqueue = cw_enqueue;
}