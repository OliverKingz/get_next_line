/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:47:21 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/10 23:09:05 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Computes the length of a string.
 * @param s The string to measure.
 * @return The number of characters in the string,
	excluding the null terminator.
 * @note If `str` is NULL, the behavior is undefined.
 */
size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return ((size_t)len);
}

/**
 * @brief Creates a substring from a string.
 * @param s The string to create a substring from.
 * @param start The index of the character in 's' to start from.
 * @param len The maximum length of the substring.
 * @return A pointer to the resulting substring, or NULL if memory allocation
 * fails.
 * @note
 * - If 'start' is beyond the length of 's', an empty string is returned.
 *
 * - The function adjusts 'len' to ensure it does not exceed the length of 's'
 *   starting from 'start'.
 *
 * - Handles NULL input by returning NULL.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	if (start < s_len)
	{
		while (s[start + i] != '\0' && i < len)
		{
			subs[i] = s[start + i];
			i++;
		}
	}
	subs[i] = '\0';
	return (subs);
}

/**
 * @brief Allocates and returns a new string
 * which is the result of the concatenation of 's1' and 's2'.
 * @param s1 The first string. If NULL, it is treated as an empty string.
 * @param s2 The second string to append to 's1'. If NULL, it is treated as an
 * empty string.
 * @return A pointer to the newly allocated concatenated string, or NULL if
 * memory allocation fails.
 * @note The function uses malloc, so the caller is responsible for freeing the
 * returned string when it is no longer needed.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		joined[s1_len + i] = s2[i];
		i++;
	}
	joined[s1_len + s2_len] = '\0';
	return (joined);
}

/**
 * @brief Locates the first occurrence of a character in a string.
 * @param s The string to search.
 * @param c The character to find (interpreted as unsigned char).
 * @return A pointer to the first occurrence of the character in the string, or
 * NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}

/**
 * @brief Duplicates a given string.
 * @param s The string to duplicate.
 * @return A pointer to the newly allocated copy of the string, or NULL if
 * memory allocation fails.
 * @note The caller is responsible for freeing the returned string.
 * Does not handle NULL input, to replicate the origina function.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dup = (char *)malloc((s_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, s_len + 1);
	return (dup);
}
