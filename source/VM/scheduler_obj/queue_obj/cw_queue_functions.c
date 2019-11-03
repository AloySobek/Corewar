/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 20:25:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_queue *p_queue_instance)
{
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_queue_instance->size)
	{
		ft_printf("Player_name: %s\nPlayer_id: %d\nCarriage_id: %d\n",
		p_queue_instance->p_current_carriage->p_owner->p_name,
		p_queue_instance->p_current_carriage->p_owner->id,
		p_queue_instance->p_current_carriage->id);
		ft_printf("Carriage_registers: ");
		for (int i = 0 ; i < CW_REG_NUMBER * CW_REG_SIZE; ++i)
			ft_printf("%02x ", p_queue_instance->p_current_carriage->p_registers[i]);
		ft_printf("\n");
		++iter;
		p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
	}
}

static void		cw_peek(t_queue *p_queue_instance, t_carriage **p_peeking_carriage)
{
	if (p_peeking_carriage)
		*p_peeking_carriage = p_queue_instance->p_current_carriage;
}

static void		cw_dequeue(t_queue *p_queue_instance, t_carriage **p_deleting_carriage)
{
	t_carriage *free_tmp;

	if (p_queue_instance->p_current_carriage)
	{
		free_tmp = p_queue_instance->p_current_carriage;
		p_queue_instance->p_current_carriage->p_next->p_prev = p_queue_instance->p_current_carriage->p_prev;
		p_queue_instance->p_current_carriage->p_prev->p_next = p_queue_instance->p_current_carriage->p_next;
		if (p_queue_instance->p_current_carriage == p_queue_instance->p_current_carriage->p_next)
			p_queue_instance->p_current_carriage = NULL;
		else
			p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
		if (!p_deleting_carriage)
			free_tmp->cw_destructor(&free_tmp);
		else
			*p_deleting_carriage = free_tmp;
		p_queue_instance->size -= 1;
	}
}

static void		cw_enqueue(t_queue *p_queue_instance, t_carriage *p_adding_carraige)
{
	if (p_adding_carraige)
	{
		if (!p_queue_instance->p_current_carriage)
		{
			p_queue_instance->p_current_carriage = p_adding_carraige;
			p_queue_instance->p_current_carriage->p_next = p_adding_carraige;
			p_queue_instance->p_current_carriage->p_prev = p_adding_carraige;
			p_queue_instance->p_tail = p_adding_carraige;
			p_queue_instance->p_head = p_adding_carraige;
		}
		else
		{
			if (p_adding_carraige->id < p_queue_instance->p_head->id)
			{
				p_adding_carraige->p_next = p_queue_instance->p_head;
				p_adding_carraige->p_prev = p_queue_instance->p_head->p_prev;
				p_queue_instance->p_head->p_prev->p_next = p_adding_carraige;
				p_queue_instance->p_head->p_prev = p_adding_carraige;
				p_queue_instance->p_head = p_adding_carraige;
				p_queue_instance->p_current_carriage = p_queue_instance->p_head;
			}
			else if (p_adding_carraige->id > p_queue_instance->p_tail->id)
			{
				p_adding_carraige->p_next = p_queue_instance->p_tail;
				p_adding_carraige->p_prev = p_queue_instance->p_tail->p_prev;
				p_queue_instance->p_tail->p_prev->p_next = p_adding_carraige;
				p_queue_instance->p_tail->p_prev = p_adding_carraige;
				p_queue_instance->p_tail = p_adding_carraige;
			}
			else
			{
				while (p_queue_instance->p_current_carriage->id < p_adding_carraige->id)
					p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
				p_adding_carraige->p_next = p_queue_instance->p_current_carriage->p_next;
				p_adding_carraige->p_prev = p_queue_instance->p_current_carriage;
				p_queue_instance->p_current_carriage->p_next->p_prev = p_adding_carraige;
				p_queue_instance->p_current_carriage->p_next = p_adding_carraige;
				p_queue_instance->p_current_carriage = p_queue_instance->p_head;
			}
		}
		p_queue_instance->size += 1;
	}
}

extern void		cw_queue_functions_linker(t_queue *p_queue_instance)
{
	p_queue_instance->cw_print_content = cw_print_content;
	p_queue_instance->cw_enqueue = cw_enqueue;
	p_queue_instance->cw_dequeue = cw_dequeue;
	p_queue_instance->cw_peek = cw_peek;
}