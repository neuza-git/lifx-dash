/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:23:30 by tgascoin          #+#    #+#             */
/*   Updated: 2016/11/14 13:40:12 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lifx.h"
/*#include <stdlib.h>
#include <string.h>*/

static int		ft_tell_ac(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			j++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (j);
}

static int		ft_tell_size_ac(const char *str, char c, int i)
{
	int j;

	j = 0;
	while (str[i] != c && str[i] != '\0')
	{
		j++;
		i++;
	}
	if (j > 0)
		j--;
	return (j);
}

static char		**ft_sub_strsplit(char const *s, char c)
{
	char	**new;
	int		iac;
	int		j;
	int		i;

	iac = 0;
	i = 0;
	new = (char**)malloc(sizeof(char*) * (ft_tell_ac(s, c) + 1));
	if (new == NULL)
		return (NULL);
	while (iac < ft_tell_ac(s, c))
	{
		j = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		new[iac] = (char*)malloc(sizeof(char) * (ft_tell_size_ac(s, c, i) + 1));
		if (new[iac] == NULL)
			return (NULL);
		while (s[i] != c && s[i] != '\0')
			new[iac][j++] = s[i++];
		new[iac++][j] = '\0';
	}
	new[iac] = NULL;
	return (new);
}

char			**ft_strsplit(char const *s, char c)
{
	if (s && c)
		return (ft_sub_strsplit(s, c));
	return (NULL);
}
