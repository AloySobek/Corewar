/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_stack_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 18:19:55 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(t_stack	**pp_stack_instance)
{
	;
}

static void		cw_destructor(t_stack **pp_stack_instance)
{
	free(*pp_stack_instance);
	*pp_stack_instance = NULL;
}

extern void		cw_create_instance_stack(t_stack **pp_stack_obj)
{
	if (!(*pp_stack_obj = (t_stack *)malloc(sizeof(t_stack))))
		cw_error_catcher(CW_NOT_ALLOCATED, "Stack has not been created");
	ft_memset(*pp_stack_obj, 0, sizeof(t_stack));
	(*pp_stack_obj)->cw_constructor = cw_constructor;
	(*pp_stack_obj)->cw_destructor = cw_destructor;
	(*pp_stack_obj)->cw_constructor(pp_stack_obj);
	cw_stack_functions_linker(*pp_stack_obj);
}