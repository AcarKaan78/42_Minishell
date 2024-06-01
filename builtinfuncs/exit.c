/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:53:32 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:22:46 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exitcmd(t_data *data)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit                                        \n", data->starttext);
	printf("\t\033[32m   _____\n");
	printf("\t  /     \\\n");
	printf("\t /       \\\n");
	printf("\t|   .   . |\n");
	printf("\t|  ´   ´  |\n");
	printf("\t|   ___   |\n");
	printf("\t|  /   \\  |\n");
	printf("\t \\       /\n");
	printf("\t  \\_____/\n\n\033[0m");
	exit(0);
}
