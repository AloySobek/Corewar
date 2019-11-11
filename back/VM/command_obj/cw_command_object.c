/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 18:59:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_command **pp_command_instance)
{
	;
}

static void	cw_destructor(t_command **pp_command_instance)
{
	free(*pp_command_instance);
	*pp_command_instance = NULL;
}

extern void	cw_create_instance_command(t_command **pp_command_obj)
{
	if (!(*pp_command_obj = (t_command *)malloc(sizeof(t_command))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_COMMAND);
	ft_memset(*pp_command_obj, 0, sizeof(t_command));
	(*pp_command_obj)->cw_constructor = cw_constructor;
	(*pp_command_obj)->cw_destructor = cw_destructor;
	(*pp_command_obj)->cw_recognize = cw_recognize_command;
	(*pp_command_obj)->cw_put_param = cw_put_param;
	(*pp_command_obj)->cw_constructor(pp_command_obj);
}
