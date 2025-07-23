/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:15:39 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/18 15:17:20 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_file(char *route)
{
	struct stat	info;

	if (stat(route, &info) != 0)
		return (0);
	return (S_ISREG(info.st_mode));
}

int	is_directory(char *route)
{
	struct stat	info;

	if (stat(route, &info) != 0)
		return (0);
	return (S_ISDIR(info.st_mode));
}
