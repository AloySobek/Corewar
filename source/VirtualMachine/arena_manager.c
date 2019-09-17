/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/17 21:17:13 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void		print_arena(corewar_t *game)
{
	int		border;
	int		i;

	border	= sqrt(MEM_SIZE);
	i		= 0;
	while (i < MEM_SIZE)
	{
		printf("%.2x | ", game->arena[i]);
		if ((i + 1) % border == 0 && i > 10)
			printf("\n");
		++i;
	}
}

int				arrange_units(corewar_t *game)
{
	int			arena_carriage;
	int			memory_step;
	int			iter;

	iter = 0;
	memory_step = MEM_SIZE / game->players_amount;
	while (iter < game->players_amount)
	{
		arena_carriage = memory_step * iter;
		game->players[iter]->reading_carriage = 0;
		add_carriage(game->carriage_list, new_carriage(game->players[iter]->id, game->players[iter]->id, arena_carriage, game->players[iter]->code[game->players[iter]->reading_carriage], get_waiting_time(game->players[iter]->code[game->players[iter]->reading_carriage]), ));
		while (arena_carriage < memory_step * iter + CHAMP_MAX_SIZE)
			game->arena[arena_carriage++] = game->players[iter]->code[game->players[iter]->reading_carriage++];
		++iter;
	}
	print_arena(game);
	return (0);
}

void			arena_init(corewar_t *game)
{
	arena_t		*new_arena;

	if (!(new_arena = (arena_t *)malloc(sizeof(arena_t))))
		exit(-1);
	if (!(new_arena->field = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		exit(-1);
	game->memory_status.arena_detect = TRUE;
	ft_memset(new_arena->field, 0, MEM_SIZE);
	new_arena->last_survivor	= game->players[game->players_amount - 1];
	new_arena->loop_amount 		= 0;
	new_arena->live_amount		= 0;
	new_arena->check_amount		= 0;
	new_arena->cycle_to_die		= CYCLE_TO_DIE;
	game->arena					= new_arena;
}