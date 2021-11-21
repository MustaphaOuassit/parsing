#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_null(const char *s)
{
	char	*dst;

    if (s == 0)
        return (0);
	dst = malloc(ft_strlen(s) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, (char *)s);
	return (dst);
}
