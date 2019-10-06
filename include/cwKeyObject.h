/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwKeyObject.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:21:54 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 19:56:26 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_KEY_OBJECT_H
# define CW_KEY_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct				key_s
{
	int						userId;
	int						userDump;
	unsigned int			loadDump;
	unsigned int			customId;
	unsigned int			graphics;

	const void				(*cwConstructorKey)		(key_t *);
	const void				(*cwValidateArgs)		(key_t *, int, char **);
	const void				(*cwReadKeys)			(key_t *, int, char **);
	const void				(*cwDestructorKey)		(key_t *);
}							key_t;

#endif