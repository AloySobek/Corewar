/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_movements_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 17:21:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_save_pos(t_process *p_process_instance, int which_exactly)
{
	if (which_exactly == PR_MAIN_SAVE)
	{
		PR_ODOMETER_I = 0;
		PR_SAVE_POINT_I = PR_CURRENT_LOCATION_I;
	}
	else if (which_exactly == PR_ADDIT_SAVE)
	{
		PR_ADDIT_SAVE_POINT_I = PR_CURRENT_LOCATION_I;
		PR_ADDIT_ODOMETER_I = PR_ODOMETER_I;
	}
	else
		cw_error_catcher(PR_OBJECT_NAME, PR_SAVE_ERROR, __FILE__, __LINE__);
}

static void	cw_move_to(t_process *p_process_instance, int distance)
{
	PR_CURRENT_LOCATION_I = (PR_CURRENT_LOCATION_I + distance) % MEM_SIZE;
	if (PR_CURRENT_LOCATION_I < 0)
		PR_CURRENT_LOCATION_I = MEM_SIZE + PR_CURRENT_LOCATION_I;
	PR_ODOMETER_I += (distance % MEM_SIZE);
}

static void	cw_carriage_return(t_process *p_process_instance, int where_exactly)
{
	if (where_exactly == PR_MAIN_SAVE)
	{
		PR_ODOMETER_I = 0;
		PR_CURRENT_LOCATION_I = PR_SAVE_POINT_I;
	}
	else if (where_exactly == PR_ADDIT_SAVE)
	{
		PR_CURRENT_LOCATION_I = PR_ADDIT_SAVE_POINT_I;
		PR_ODOMETER_I = PR_ADDIT_ODOMETER_I;
	}
	else
		cw_error_catcher(PR_OBJECT_ERROR, PR_RETURN_ERROR, __FILE__, __LINE__);
}

static void	cw_parse_types(t_process *p_process_instance, t_arena *p_arena_obj)
{
	// t_mark	s;
	// t_iter	i;

	// i = CW_ITERATOR;
	// p_process_instance->cw_move_to(p_process_instance, PR_NAME_PASS);
	// PR_ARGS_I = AR_FIELD_O[PR_CURRENT_LOCATION_I];
	// if (PR_CURRENT_COMMAND_I->type_byte)
	// 	while (++i < 3 && (s = PR_CURRENT_COMMAND_I->args >> (24 - (i * 8)) & 0xff) >= 0)
	// 	{
	// 		if (s)
	// 		{
	// 			if ((PR_ARGS_I >> PR_SHIFT(6) ? PR_STUB : (s >> 6 & 0x03))
	// 			&& (PR_ARGS_I >> PR_SHIFT(4) ? PR_STUB : (s >> 4 & 0x03))
	// 			&& (PR_ARGS_I >> PR_SHIFT(2) ? PR_STUB : (s >> 2 & 0x03)))
	// 				PR_ERROR_OCCURED_I = CW_TRUE;
	// 			PR_REG_CHECK ? PR_OFFSET_I += CW_REG_CODE_SIZE : 0;
	// 			PR_DIR_CHECK ? PR_OFFSET_I += PR_CURRENT_COMMAND_I->dir_size : 0;
	// 			PR_IND_CHECK ? PR_OFFSET_I += CW_IND_CODE_SIZE : 0;
	// 			if ((PR_ARGS_I >> (6 - (i * 2)) & 0x03) == CW_REG_CODE && !PR_ERROR_OCCURED_I)
	// 				if (AR_FIELD_O[(PR_CURRENT_LOCATION_I + PR_OFFSET_I) % MEM_SIZE] < 1
	// 				|| AR_FIELD_O[(PR_CURRENT_LOCATION_I + PR_OFFSET_I) % MEM_SIZE] > 16)
	// 					PR_ERROR_OCCURED_I = CW_TRUE;
	// 		}
	// 		else
	// 			PR_ARGS_I = (PR_ARGS_I >> (6 - (i * 2))) << (6 - (i * 2));
	// 	}
	// else
	// 	PR_ARGS_I = 0x80;
	// p_process_instance->cw_move_to(p_process_instance, PR_CURRENT_COMMAND_I->type_byte);
	// PR_ERROR_OCCURED_I ? p_process_instance->cw_move_to(p_process_instance, PR_OFFSET_I) : 0;
	t_mark	sample;
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
	if (p_process_instance->error_ocurred && p_process_instance->p_current_command->type_byte)
		p_process_instance->cw_move_to(p_process_instance, p_process_instance->offset);
}

extern void	cw_process_movements_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_save_pos = cw_save_pos;
	p_process_instance->cw_parse_types = cw_parse_types;
	p_process_instance->cw_move_to = cw_move_to;
	p_process_instance->cw_carriage_return = cw_carriage_return;
}
