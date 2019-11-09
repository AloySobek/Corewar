/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_read_write_functions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:10:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 20:12:33 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_write_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
{
	t_iter	i;

	i = CW_ITERATOR;
	if (input_arg == CW_REG_CODE)
	{
		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
		while (++i < CW_REG_SIZE)
			PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE] = BU_DATA_O[i];
		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
	}
	else if (input_arg == CW_IND_CODE)
	{
		AR_BUFFERS_O[CW_SYSTEM_BUF]->cw_erase_data(AR_BUFFERS_O[CW_SYSTEM_BUF]);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
			AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_conversion_bytes_to_value(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF], CW_SHORT);
		if (p_process_instance->p_current_command->id != CO_LLD)
			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
		AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
		p_process_instance->cw_move_to	(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value - p_process_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
			p_arena_obj->p_field[PR_CURRENT_LOCATION_I] = BU_DATA_O[i];
		p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
	}
	else
		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
}

void	cw_read_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
{
	if (input_arg == CW_REG_CODE)
	{
		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			BU_DATA_O[i] = PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE];
		p_process_instance->cw_conversion_bytes_to_value(p_process_instance, p_buffer_obj, CW_INT);
		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
	}
	else if (input_arg == CW_DIR_CODE)
	{
		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
		for (int i = 4 - p_process_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_conversion_bytes_to_value(p_process_instance, p_buffer_obj, 4 - p_process_instance->p_current_command->dir_size);
	}
	else if (input_arg == CW_IND_CODE)
	{
		ft_memset(AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
			AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_conversion_bytes_to_value(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF], CW_SHORT);
		if (p_process_instance->p_current_command->id != CO_LLD)
			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
		p_process_instance->cw_move_to(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value - p_process_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_conversion_bytes_to_value(p_process_instance, p_buffer_obj, CW_INT);
		p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
	}
	else
		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
}

extern void	cw_process_read_write_functions_linker(t_process *p_process_linker)
{
	p_process_linker->cw_read_operation = cw_read_operation;
	p_process_linker->cw_write_operation = cw_write_operation;
}
