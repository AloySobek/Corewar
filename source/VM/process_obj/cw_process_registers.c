/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_registers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 16:04:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_reg_check(t_process *p_carriage_instance, t_arena *p_arena_obj, int type, int *found)
{
	if (!*found)
		return ;
	if (type == CW_REG_CODE)
	{
		p_carriage_instance->offset += CW_REG_CODE_SIZE;
		if (p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] < 1
		|| p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] > 16)
		{
			p_carriage_instance->error_ocurred = CW_TRUE;
			*found = CW_FALSE;
		}
	}
	else if (type == CW_DIR_CODE)
		p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size;
	else if (type == CW_IND_CODE)
		p_carriage_instance->offset += CW_IND_CODE_SIZE;
}

void	cw_copy_reg(t_process *p_carriage_instance, t_process *p_copying_carriage)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE * 16)
		p_copying_carriage->p_registers[iter] = p_carriage_instance->p_registers[iter];
}

void	cw_write_owner_id_to_reg(t_process *p_carriage_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE)
		p_carriage_instance->p_registers[iter] = (-p_carriage_instance->p_owner->id << (iter * 8)) >> 24;
}

void	cw_check_carry(t_process *p_carriage_instance)
{
	int		iter;

	iter = p_carriage_instance->current_register * CW_REG_SIZE - 1;
	while (++iter < (p_carriage_instance->current_register + 1) * CW_REG_SIZE)
		if (p_carriage_instance->p_registers[iter] != 0 && !(p_carriage_instance->carry = 0))
			return ;
	p_carriage_instance->carry = 1;
}

void	cw_conversion_value_to_bytes(t_process *pCarraigeInstance, t_buffer *pBufferObj, int type)
{
	ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->p_data[type] = pBufferObj->s_types.int_value >> (24 - (type * 8)) & 0xff;
		++type;
	}
}

void	cw_conversion_bytes_to_value(t_process *pCarraigeInstance, t_buffer *pBufferObj, int type)
{
	pBufferObj->s_types.int_value = 0;
	while (type < CW_REG_SIZE)
	{
		pBufferObj->s_types.int_value |= pBufferObj->p_data[type] << ((3 - type) * 8);
		++type;
	}
}

// static void	cw_copy_reg(t_process *p_process_instance, t_process *p_process_obj)
// {
// 	int		iter;

// 	iter = CW_ITERATOR;
// 	while (++iter < CW_REG_SIZE * 16)
// 		PR_REGISTERS_O[iter] = PR_REGISTERS_I[iter];
// }

// static void	cw_write_owner_id_to_reg(t_process *p_process_instance)
// {
// 	int		iter;

// 	iter = CW_ITERATOR;
// 	while (++iter < CW_REG_SIZE)
// 		PR_REGISTERS_I[iter] = (-PR_OWNER_I->id << (iter * 8)) >> 24;
// }

// static void	cw_check_carry(t_process *p_process_instance)
// {
// 	int		iter;

// 	iter = PR_CURRENT_REGISTER_I * CW_REG_SIZE - 1;
// 	while (++iter < (PR_CURRENT_REGISTER_I + 1) * CW_REG_SIZE)
// 		if (PR_REGISTERS_I[iter] != 0 && !(PR_CARRY_I = 0))
// 			return ;
// 	PR_CARRY_I = 1;
// }

// static void	cw_conversion_value_to_bytes(t_process *p_process_instance, t_buffer *p_buffer_obj, int type)
// {
// 	ft_memset(p_buffer_obj->p_data, 0, CW_REG_SIZE);
// 	while (type < CW_REG_SIZE)
// 	{
// 		p_buffer_obj->p_data[type] = p_buffer_obj->s_types.int_value >> (24 - (type * 8)) & 0xff;
// 		++type;
// 	}
// }

// static void	cw_conversion_bytes_to_value(t_process *p_process_instance, t_buffer *p_buffer_obj, int type)
// {
// 	p_buffer_obj->s_types.int_value = 0;
// 	while (type < CW_REG_SIZE)
// 	{
// 		p_buffer_obj->s_types.int_value |= p_buffer_obj->p_data[type] << ((3 - type) * 8);
// 		++type;
// 	}
// }

// static void	cw_conversion(t_process *p_process_instance, t_buffer *p_buffer_obj,
// 							int type, int mode)
// {
// 	type -= 1;
// 	if (mode == PR_VALUE)
// 	{
// 		p_buffer_obj->cw_erase_data(p_buffer_obj);
// 		while (++type < CW_REG_SIZE)
// 			BU_DATA_O[type] = BU_INT_VALUE_O >> (24 - (type * 8)) & 0xff;
// 	}
// 	else if (mode == PR_BYTE)
// 	{
// 		BU_INT_VALUE_O = 0;
// 		while (++type < CW_REG_SIZE)
// 			BU_INT_VALUE_O |= BU_DATA_O[type] << ((3 - type) * 8);
// 	}
// }

extern void	cw_process_registers_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_write_owner_id_to_reg = cw_write_owner_id_to_reg;
	p_process_instance->cw_check_carry = cw_check_carry;
	p_process_instance->cw_conversion_bytes_to_value = cw_conversion_bytes_to_value;
	p_process_instance->cw_conversion_value_to_bytes = cw_conversion_value_to_bytes;
	p_process_instance->cw_copy_reg = cw_copy_reg;
}
