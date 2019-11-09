/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_registers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 20:17:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_copy_reg(t_process *p_process_instance, t_process *p_process_obj)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE * 16)
		p_process_obj->p_registers[iter] = p_process_instance->p_registers[iter];
}

static void	cw_write_owner_id_to_reg(t_process *p_process_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE)
		p_process_instance->p_registers[iter] = (-p_process_instance->p_owner->id << (iter * 8)) >> 24;
}

static void	cw_check_carry(t_process *p_process_instance)
{
	int		iter;

	iter = p_process_instance->current_register * CW_REG_SIZE - 1;
	while (++iter < (p_process_instance->current_register + 1) * CW_REG_SIZE)
		if (p_process_instance->p_registers[iter] != 0 && !(p_process_instance->carry = 0))
			return ;
	p_process_instance->carry = 1;
}

static void	cw_conversion_value_to_bytes(t_process *p_process_instance, t_buffer *p_buffer_obj, int type)
{
	ft_memset(p_buffer_obj->p_data, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		p_buffer_obj->p_data[type] = p_buffer_obj->s_types.int_value >> (24 - (type * 8)) & 0xff;
		++type;
	}
}

static void	cw_conversion_bytes_to_value(t_process *p_process_instance, t_buffer *p_buffer_obj, int type)
{
	p_buffer_obj->s_types.int_value = 0;
	while (type < CW_REG_SIZE)
	{
		p_buffer_obj->s_types.int_value |= p_buffer_obj->p_data[type] << ((3 - type) * 8);
		++type;
	}
}

extern void	cw_process_registers_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_conversion_bytes_to_value = cw_conversion_bytes_to_value;
	p_process_instance->cw_conversion_value_to_bytes = cw_conversion_value_to_bytes;
	p_process_instance->cw_check_carry = cw_check_carry;
	p_process_instance->cw_write_owner_id_to_reg = cw_write_owner_id_to_reg;
	p_process_instance->cw_copy_reg = cw_copy_reg;
}