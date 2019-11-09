/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:51:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/15 17:38:43 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*new_str;
	int		count;

	count = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!new_str)
		return (NULL);
	while (s1[count] != '\0')
	{
		new_str[count] = s1[count];
		count++;
	}
	new_str[count] = '\0';
	return (new_str);
}
