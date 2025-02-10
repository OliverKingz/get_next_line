/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:27:13 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/10 23:09:58 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ************************************************************************** */

# define MAX_FD 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************** */

# include "libft.h"

/* ************************************************************************** */
/*
 * Get Next Line Functions:
 * - get_next_line: Reads a line from the file descriptor.
 * - read_and_store: Reads from the fd with a buffer and stores the data.
 * - get_line: gets the line from the buffer stored lines
 * Functions that GNL uses from Libft:
 * - `ft_strdup`
 * - `ft_strchr`
 * - `ft_substr`
 * - `ft_strjoin`
 * - `ft_strlen`
 * - `ft_strlcpy`
 */
/* ************************************************************************** */

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

/* ************************************************************************** */
#endif