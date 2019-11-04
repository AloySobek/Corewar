/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_stack_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:56:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 17:06:36 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(t_stack *p_stack_instance)
{
	t_iterator	iter;

	iter = CW_ITERATOR;
	if (p_stack_instance->p_current_carriage)
		while (++iter < p_stack_instance->size)
		{
			ft_printf("Carriage_id: %d\n", p_stack_instance->p_current_carriage->id);
			ft_printf("Carriage_registers: ");
			for (int i = 0 ; i < CW_REG_NUMBER * CW_REG_SIZE; ++i)
				ft_printf("%02x ", p_stack_instance->p_current_carriage->p_registers[i]);
			ft_printf("\n");
			p_stack_instance->cw_rotate(p_stack_instance);
		}
	else
		while (++iter < p_stack_instance->size)
		{
			ft_printf("Player_name: %s\nPlayer_comment: %s\nPlayer_id: %d\n",
			p_stack_instance->p_current_player->p_name,
			p_stack_instance->p_current_player->p_comment,
			p_stack_instance->p_current_player->id);
			p_stack_instance->cw_rotate(p_stack_instance);
		}
}

static void		cw_peek(t_stack *p_stack_instance, t_carriage **p_peeking_carriage, t_player **p_peeking_player)
{
	if (p_peeking_carriage)
		*p_peeking_carriage = p_stack_instance->p_current_carriage;
	else if (p_peeking_player)
		*p_peeking_player = p_stack_instance->p_current_player;
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Not allowed acts with the peek function");
}

static void		cw_reverse_rotate(t_stack *p_stack_instance)
{
	if (p_stack_instance->p_current_carriage)
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_prev;
	else if (p_stack_instance->p_current_player)
		p_stack_instance->p_current_player = p_stack_instance->p_current_player->p_prev;
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Not allowed acts with the reverse_rotate function");
}

static void		cw_rotate(t_stack *p_stack_instance)
{
	if (p_stack_instance->p_current_carriage)
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_next;
	else if (p_stack_instance->p_current_player)
		p_stack_instance->p_current_player = p_stack_instance->p_current_player->p_next;
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Not allowed acts with the rotate function");
}

static void		cw_pop(t_stack *p_stack_instance, t_carriage **p_deleting_carriage, t_player **p_deleting_player)
{
	t_carriage	*process_kill;
	t_player	*player_kick;

	if (p_stack_instance->p_current_carriage)
	{
		process_kill = p_stack_instance->p_current_carriage;
		p_stack_instance->p_current_carriage->p_next->p_prev = p_stack_instance->p_current_carriage->p_prev;
		p_stack_instance->p_current_carriage->p_prev->p_next = p_stack_instance->p_current_carriage->p_next;
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_next;
		process_kill->p_next = NULL;
		process_kill->p_prev = NULL;
		if (!p_deleting_carriage)
		{
			if (p_stack_instance->p_current_carriage == process_kill)
				p_stack_instance->p_current_carriage = NULL;
			process_kill->cw_destructor(&process_kill);
		}
		else
			*p_deleting_carriage = process_kill;
		p_stack_instance->size -= 1;
	}
	else if (p_stack_instance->p_current_player)
	{
		player_kick = p_stack_instance->p_current_player;
		p_stack_instance->p_current_player->p_next->p_prev = p_stack_instance->p_current_player->p_prev;
		p_stack_instance->p_current_player->p_prev->p_next = p_stack_instance->p_current_player->p_next;
		p_stack_instance->p_current_player = p_stack_instance->p_current_player->p_next;
		player_kick->p_next = NULL;
		player_kick->p_prev = NULL;
		if (!p_deleting_player)
		{
			if (p_stack_instance->p_current_player == player_kick)
				p_stack_instance->p_current_player = NULL;
			player_kick->cw_destructor(&player_kick);
		}
		else
			*p_deleting_player = player_kick;
		p_stack_instance->size -= 1;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Not allowed acts with pop function");
}

static void		cw_push(t_stack *p_stack_instance, t_carriage *p_adding_carriage, t_player *p_adding_player)
{
	if (p_adding_carriage)
	{
		if (!p_stack_instance->p_current_carriage)
		{
			p_stack_instance->p_current_carriage = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_next = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_prev = p_adding_carriage;
		}
		else
		{
			p_adding_carriage->p_next = p_stack_instance->p_current_carriage;
			p_adding_carriage->p_prev = p_stack_instance->p_current_carriage->p_prev;
			p_stack_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_prev = p_adding_carriage;
			p_stack_instance->p_current_carriage = p_adding_carriage;
		}
		p_stack_instance->size += 1;
	}
	else if (p_adding_player)
	{
		if (!p_stack_instance->p_current_player)
		{
			p_stack_instance->p_current_player = p_adding_player;
			p_stack_instance->p_current_player->p_next = p_adding_player;
			p_stack_instance->p_current_player->p_prev = p_adding_player;
		}
		else
		{
			p_adding_player->p_next = p_stack_instance->p_current_player;
			p_adding_player->p_prev = p_stack_instance->p_current_player->p_prev;
			p_stack_instance->p_current_player->p_prev->p_next = p_adding_player;
			p_stack_instance->p_current_player->p_prev = p_adding_player;
			p_stack_instance->p_current_player = p_adding_player;
		}
		p_stack_instance->size += 1;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Not allowed acts with push function");
}

extern void	cw_stack_functions_linker(t_stack *p_stack_instance)
{
	p_stack_instance->cw_reverse_rotate = cw_reverse_rotate;
	p_stack_instance->cw_print_content = cw_print_content;
	p_stack_instance->cw_rotate = cw_rotate;
	p_stack_instance->cw_push = cw_push;
	p_stack_instance->cw_peek = cw_peek;
	p_stack_instance->cw_pop = cw_pop;
}