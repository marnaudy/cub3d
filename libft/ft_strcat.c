/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:03:57 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/07 16:16:06 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = 0;
	free(s1);
	free(s2);
	return (new);
}
