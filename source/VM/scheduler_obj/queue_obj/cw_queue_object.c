/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:13:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/05 18:19:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(t_queue **pp_queue_instance)
{
	;
}

static void		cw_destructor(t_queue **pp_queue_instance)
{
	free(*pp_queue_instance);
	*pp_queue_instance = NULL;
}

extern void		cw_create_instance_queue(t_queue **pp_queue_obj)
{
	if (!(*pp_queue_obj = (t_queue *)malloc(sizeof(t_queue))))
		cw_error_catcher(CW_NOT_ALLOCATED, "Queue object has not been created");
	ft_memset(*pp_queue_obj, 0, sizeof(t_queue));
	(*pp_queue_obj)->cw_constructor = cw_constructor;
	(*pp_queue_obj)->cw_destructor = cw_destructor;
	(*pp_queue_obj)->cw_constructor(pp_queue_obj);
	cw_queue_functions_linker(*pp_queue_obj);
}