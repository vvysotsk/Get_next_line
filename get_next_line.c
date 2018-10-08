/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:57:25 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/03/13 16:57:26 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		write_in_line(int fd, char *puck[fd], char **line)
{
	if (ft_strchr(puck[fd], '\n'))
		*line = ft_strsub(puck[fd], 0, ft_strchr(puck[fd], '\n') - puck[fd]);
	else
		*line = ft_strdup(puck[fd]);
}

static void		find_next_line(int fd, char *puck[fd])
{
	int			index;
	char		*leak;

	index = ft_strchr(puck[fd], '\n') - puck[fd] + 1;
	if (ft_strchr(puck[fd], '\n'))
	{
		leak = puck[fd];
		puck[fd] = ft_strsub(puck[fd], index, ft_strlen(puck[fd]));
		free(leak);
	}
	else
		ft_strdel(&puck[fd]);
}

static int		build_line(char **puck, const int fd)
{
	char		buff[BUFF_SIZE + 1];
	char		*leak;
	int			i;

	while (!ft_strchr(puck[fd], '\n') && (i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		leak = puck[fd];
		buff[i] = '\0';
		puck[fd] = ft_strjoin(puck[fd], buff);
		free(leak);
	}
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	static char	*puck[2000000];
	int			i;

	if (fd < 0 || fd > 4864 || !line)
		return (-1);
	if (puck[fd] == NULL)
		puck[fd] = ft_strnew(1);
	if (puck[fd] == NULL)
		return (-1);
	i = build_line(puck, fd);
	if (i < 0)
		return (-1);
	write_in_line(fd, puck, line);
	find_next_line(fd, puck);
	if (!puck[fd] && ft_strlen(*line) == 0)
		return (0);
	return (1);
}
