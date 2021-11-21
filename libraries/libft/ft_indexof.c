# include "libft.h"

int		ft_indexof(char *str, char c)
{
	int i;

	i = 0;

	while(str[i] != '\0')
	{
		if (str[i] == c)
			break;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}