/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 19:53:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "cr_vis.h"

# include "cw_obj_container.h"

/*
** Subject's defines
** -----------------------------------
*/

# define MAX_ARGS_NUMBER		4
# define CW_MAX_PLAYERS			4
# define CW_MIN_PLAYERS			1
# define CW_MIN_DUMP_CYCLE		1
# define CW_ALL_FREE			0x4030201
# define SIZE_BINARY_LABEL		4
# define NULL_SEPARATOR			4
# define SIZE_VARIABLE			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
**-------------------------------------
*/

typedef enum				e_byte_blocks
{
	BINARY_LABEL = SIZE_BINARY_LABEL,
	NAME = BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE = NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT = CODE_SIZE + COMMENT_LENGTH,
	CODE = COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							t_byte_blocks;

# define CW_CHAR				3
# define CW_SHORT				2
# define CW_INT					0
# define CW_REG_NUMBER			16

/*
** Error's Defines
** -------------------------------------------
*/

# define CW_NOT_ALLOCATED		1
# define CW_NOT_VALID_KEY		2
# define CW_OPEN_FILE_ERROR		3
# define CW_READ_FILE_ERROR		4
# define CW_INCORRECT_BINARY	5
# define CW_TOO_BIG_SIZE		6
# define CW_CHEAT_DETECT		7
# define CW_ARGS_AMOUN_ERROR	8
# define CW_INVALID_PLAYERS		9
# define CW_KERNEL_ERROR		10

# define CW_GAME				"Game"
# define CW_KEYS				"Keys"
# define CW_PLAYER				"Player"
# define CW_CARRIAGE			"Carriage"
# define CW_ARENA				"Arena"
# define CW_COMMAND				"Command"
# define CW_INIT				"Initialization"
# define CW_EXEC_ERROR			"In Exec error"

/*
** ------------------------------------------
*/

/*
** Common defines;
** -----------------------------
*/

# define CW_SUCCESS				0

# define CW_BEGIN_FROM_ZERO		0x00
# define CW_BEGIN_FROM_ONE		0x01
# define CW_ITERATOR			-1
# define CW_TRUE				0x01
# define CW_FALSE				0x00

# define CW_REG					0x40
# define CW_REG_CODE			0x01
# define CW_REG_CODE_SIZE		0x01
# define CW_REG_SIZE			0x04

# define CW_DIR					0x20
# define CW_DIR_CODE			0x02
# define CW_DIR_CODE_SIZE		4
# define CW_SHDIR_CODE_SIZE		0x02

# define CW_IND					0x0c
# define CW_IND_CODE			0x03
# define CW_IND_CODE_SIZE		0x02
# define CW_IND_SIZE			0x04

# define CW_KEY					'-'

# define CW_NAME_PASS			1

# define CW_MAIN_SAVE			1
# define CW_ADDIT_SAVE			2

/*
** -----------------------------
*/

/*
** Command's defines
** -----------------------------
*/

# define CW_LIVE				0x01
# define CW_LD					0x02
# define CW_ST					0x03
# define CW_ADD					0x04
# define CW_SUB					0x05
# define CW_AND					0x06
# define CW_OR					0x07
# define CW_XOR					0x08
# define CW_ZJMP				0x09
# define CW_LDI					0x0a
# define CW_STI					0x0b
# define CW_FORK				0x0c
# define CW_LLD					0x0d
# define CW_LLDI				0x0e
# define CW_LFORK				0x0f
# define CW_AFF					0x10

/*
**------------------------------
*/

void							live_exec	(t_corewar *game);
void							ld_exec		(t_corewar *game);
void							st_exec		(t_corewar *game);
void							add_exec	(t_corewar *game);
void							sub_exec	(t_corewar *game);
void							and_exec	(t_corewar *game);
void							or_exec		(t_corewar *game);
void							xor_exec	(t_corewar *game);
void							zjmp_exec	(t_corewar *game);
void							ldi_exec	(t_corewar *game);
void							sti_exec	(t_corewar *game);
void							fork_exec	(t_corewar *game);
void							lld_exec	(t_corewar *game);
void							lldi_exec	(t_corewar *game);
void							lfork_exec	(t_corewar *game);
void							aff_exec	(t_corewar *game);

void							cw_create_instance_carriage(t_carriage **pp_carriage_obj);
void							cw_error_catcher(int error_code, const char *section);

#endif
