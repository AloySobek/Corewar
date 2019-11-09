/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:58:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_process **pp_process_instance)
{
	if (!((*pp_process_instance)->p_registers = (unsigned char *)malloc(sizeof(unsigned char) * (CW_REG_NUMBER * CW_REG_SIZE))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset((*pp_process_instance)->p_registers, 0, CW_REG_NUMBER * CW_REG_SIZE);
	(*pp_process_instance)->nearest_cycle = 1;
}

static void	cw_destructor(t_process **pp_process_instance)
{
	free((*pp_process_instance)->p_registers);
	free((*pp_process_instance));
	*pp_process_instance = NULL;
}

extern void	cw_create_instance_carriage(t_process **pp_carriage_obj)
{
	if (!(*pp_carriage_obj = (t_process *)malloc(sizeof(t_process))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset(*pp_carriage_obj, 0, sizeof(t_process));
	(*pp_carriage_obj)->cw_constructor = cw_constructor;
	(*pp_carriage_obj)->cw_destructor = cw_destructor;
	(*pp_carriage_obj)->cw_conversion_value_to_bytes = cw_conversion_value_to_bytes;
	(*pp_carriage_obj)->cw_conversion_bytes_to_value = cw_conversion_bytes_to_value;
	(*pp_carriage_obj)->cw_read_operation = cw_read_operation;
	(*pp_carriage_obj)->cw_write_operation = cw_write_operation;
	(*pp_carriage_obj)->cw_parse_types = cw_parse_types;
	(*pp_carriage_obj)->cw_check_carry = cw_check_carry;
	(*pp_carriage_obj)->cw_save_pos = cw_save_pos;
	(*pp_carriage_obj)->cw_move_to = cw_move_to;
	(*pp_carriage_obj)->cw_exec_command = cw_exec_command;
	(*pp_carriage_obj)->cw_set_command_time = cw_set_command_time;
	(*pp_carriage_obj)->cw_write_owner_id_to_reg = cw_write_owner_id_to_reg;
	(*pp_carriage_obj)->cw_carriage_return = cw_carriage_return;
	(*pp_carriage_obj)->cw_skip_damaged_command = cw_skip_damaged_command;
	(*pp_carriage_obj)->cw_set_owner = cw_set_owner;
	(*pp_carriage_obj)->cw_copy_reg = cw_copy_reg;
	(*pp_carriage_obj)->cw_reg_check = cw_reg_check;
	(*pp_carriage_obj)->cw_constructor(pp_carriage_obj);
}
