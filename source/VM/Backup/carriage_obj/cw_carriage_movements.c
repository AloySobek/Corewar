/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_movements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:58:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_save_pos(t_process *p_process_instance, int whichExactly)
{
	if (whichExactly == CW_MAIN_SAVE)
	{
		p_process_instance->odometer = 0;
		p_process_instance->save_point	= p_process_instance->current_location;
	}
	else if (whichExactly == CW_ADDIT_SAVE)
	{
		p_process_instance->addit_save_point = p_process_instance->current_location;
		p_process_instance->addit_odometer = p_process_instance->odometer;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Save_pos error");
}

void	cw_move_to(t_process *pCarraigeInstance, int distance)
{
	pCarraigeInstance->current_location = (pCarraigeInstance->current_location + distance) % MEM_SIZE;
	if (pCarraigeInstance->current_location < 0)
		pCarraigeInstance->current_location	= MEM_SIZE + pCarraigeInstance->current_location;
	pCarraigeInstance->odometer += (distance % MEM_SIZE);
}

void	cw_carriage_return(t_process *p_process_instance, int whereExactly)
{
	if (whereExactly == CW_MAIN_SAVE)
	{
		p_process_instance->odometer = 0;
		p_process_instance->current_location = p_process_instance->save_point;
	}
	else if (whereExactly == CW_ADDIT_SAVE)
	{
		p_process_instance->current_location = p_process_instance->addit_save_point;
		p_process_instance->odometer = p_process_instance->addit_odometer;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Return carriage error");
}

void		cw_skip_damaged_command(t_process *p_process_instance, t_arena *p_arena_obj)
{
	if (p_process_instance->p_current_command->type_byte)
		p_process_instance->cw_move_to(p_process_instance, p_process_instance->offset);
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Error occured while skipping damaged command");
}

void	cw_parse_types(t_process *p_process_instance, t_arena *p_arena_obj)
{
	int		sample;;
	int		iter;

	iter = CW_ITERATOR;
	p_process_instance->cw_move_to(p_process_instance, CW_NAME_PASS);
	p_process_instance->args = p_arena_obj->p_field[p_process_instance->current_location];
	if (p_process_instance->p_current_command->type_byte)
		while (++iter < 3)
		{
			sample = p_process_instance->p_current_command->args >> (24 - (iter * 8)) & 0xff;
			if (sample)
			{
				if ((p_process_instance->args >> (6 - (iter * 2)) & 0x03) != (!(sample >> 6 & 0x03) ? 2147483647 : (sample >> 6 & 0x03))
					&& (p_process_instance->args >> (6 - (iter * 2)) & 0x03) != (!(sample >> 4 & 0x03) ? 2147483647 : (sample >> 4 & 0x03))
					&& (p_process_instance->args >> (6 - (iter * 2)) & 0x03) != (!(sample >> 2 & 0x03) ? 2147483647 : (sample >> 2 & 0x03)))
					p_process_instance->error_ocurred = CW_TRUE;
				(p_process_instance->args >> (6 - (iter * 2)) & 0x03) == CW_REG_CODE ? p_process_instance->offset += CW_REG_CODE_SIZE : CW_FALSE;
				(p_process_instance->args >> (6 - (iter * 2)) & 0x03) == CW_DIR_CODE ? p_process_instance->offset += p_process_instance->p_current_command->dir_size : CW_FALSE;
				(p_process_instance->args >> (6 - (iter * 2)) & 0x03) == CW_IND_CODE ? p_process_instance->offset += CW_IND_CODE_SIZE : CW_FALSE;
				if ((p_process_instance->args >> (6 - (iter * 2)) & 0x03) == CW_REG_CODE && !p_process_instance->error_ocurred)
					if (p_arena_obj->p_field[(p_process_instance->current_location + p_process_instance->offset) % MEM_SIZE] < 1
					|| p_arena_obj->p_field[(p_process_instance->current_location + p_process_instance->offset) % MEM_SIZE] > 16)
						p_process_instance->error_ocurred = CW_TRUE;
			}
			else
				p_process_instance->args = (p_process_instance->args >> (6 - (iter * 2))) << (6 - (iter * 2));
		}
	else
		p_process_instance->args = 0x80;
	p_process_instance->cw_move_to(p_process_instance, p_process_instance->p_current_command->type_byte);
	if (p_process_instance->error_ocurred)
		p_process_instance->cw_skip_damaged_command(p_process_instance, p_arena_obj);
}