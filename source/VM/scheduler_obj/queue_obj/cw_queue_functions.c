/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 21:03:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_queue *p_queue_instance)
{
	int			iter;

	iter = CW_ITERATOR;
	while (++iter < p_queue_instance->size)
	{
		ft_printf("Carriage_id: %d\nNearest_cycle: %d\n",
		p_queue_instance->p_current_carriage->id,
		p_queue_instance->p_current_carriage->nearest_cycle);
		ft_printf("Carriage_registers: ");
		for (int i = 0 ; i < CW_REG_NUMBER * CW_REG_SIZE; ++i)
			ft_printf("%02x ", p_queue_instance->p_current_carriage->p_registers[i]);
		ft_printf("\n");
		p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
	}
}

static void		cw_peek(t_queue *p_queue_instance, t_carriage **p_peeking_carriage)
{
	if (p_peeking_carriage)
		*p_peeking_carriage = p_queue_instance->p_current_carriage;
}

static void		cw_rotate(t_queue *p_queue_instance)
{
	if (p_queue_instance->p_current_carriage)
		p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
}

static void		cw_dequeue(t_queue *p_queue_instance, t_carriage **p_deleting_carriage)
{
	t_carriage *kill_process;

	if (p_queue_instance->p_current_carriage)
	{
		kill_process = p_queue_instance->p_current_carriage;
		if (p_queue_instance->p_current_carriage == p_queue_instance->p_current_carriage->p_next)
			p_queue_instance->p_current_carriage = NULL;
		else
		{
			p_queue_instance->p_current_carriage->p_next->p_prev = p_queue_instance->p_current_carriage->p_prev;
			p_queue_instance->p_current_carriage->p_prev->p_next = p_queue_instance->p_current_carriage->p_next;
			p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
		}
		if (!p_deleting_carriage)
			kill_process->cw_destructor(&kill_process);
		else
			*p_deleting_carriage = kill_process;
		p_queue_instance->size -= 1;
	}
}

static void		cw_quant_enqueue(t_queue *p_queue_instance, t_carriage *p_adding_carriage)
{
	int			iter;

	iter = CW_ITERATOR;
	if (p_adding_carriage)
	{
		if (!p_queue_instance->p_current_carriage)
		{
			p_queue_instance->p_current_carriage = p_adding_carriage;
			p_queue_instance->p_current_carriage->p_next = p_adding_carriage;
			p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
		}
		else
		{
			if (p_adding_carriage->nearest_cycle < p_queue_instance->p_current_carriage->nearest_cycle)
			{
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
				p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
				p_queue_instance->p_current_carriage = p_adding_carriage;
			}
			else if (p_adding_carriage->nearest_cycle > p_queue_instance->p_current_carriage->p_prev->nearest_cycle)
			{
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
				p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
			}
			else
			{
				p_queue_instance->p_head = p_queue_instance->p_current_carriage;
				while (p_adding_carriage->nearest_cycle > p_queue_instance->p_current_carriage->nearest_cycle)
					p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
				while (p_adding_carriage->nearest_cycle == p_queue_instance->p_current_carriage->nearest_cycle && p_adding_carriage->id < p_queue_instance->p_current_carriage->id && ++iter <= p_queue_instance->size)
					p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
				p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
				p_queue_instance->p_current_carriage = p_queue_instance->p_head;
			}
		}
		p_queue_instance->size += 1;
	}
}

static void		cw_enqueue(t_queue *p_queue_instance, t_carriage *p_adding_carriage)
{
	if (p_adding_carriage)
	{
		if (!p_queue_instance->p_current_carriage)
		{
			p_queue_instance->p_current_carriage = p_adding_carriage;
			p_queue_instance->p_current_carriage->p_next = p_adding_carriage;
			p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
		}
		else
		{
			if (p_adding_carriage->id > p_queue_instance->p_current_carriage->id)
			{
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
				p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
				p_queue_instance->p_current_carriage = p_adding_carriage;
			}
			else if (p_adding_carriage->id < p_queue_instance->p_current_carriage->p_prev->id)
			{
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
				p_queue_instance->p_current_carriage->p_prev = p_adding_carriage;
			}
			else
			{
				p_queue_instance->p_head = p_queue_instance->p_current_carriage;
				while (p_adding_carriage->id < p_queue_instance->p_current_carriage->id)
					p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
				p_adding_carriage->p_next = p_queue_instance->p_current_carriage;
				p_adding_carriage->p_prev = p_queue_instance->p_current_carriage->p_prev;
				p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
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
	p_queue_instance->cw_quant_enqueue = cw_quant_enqueue;
	p_queue_instance->cw_rotate = cw_rotate;
}