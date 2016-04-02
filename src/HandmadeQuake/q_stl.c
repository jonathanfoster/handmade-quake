#include "quakedef.h"

int32 Q_atoi(uint8 *str)
{
	int32 sign = 1;
	int32 val = 0;
	uint8 c;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	// hexadecimal
	if (str[0] == '0' && (str[1] == 'x' || 'X'))
	{
		str += 2;

		while (1)
		{
			c = *str;
			str++;

			if (c >= '0' && c <= '9')
			{
				val = val * 16 + c - '0';
			}
			else if (c >= 'a' && c <= 'f')
			{
				val = val * 16 + c - 'a' + 10;
			}
			else if (c >= 'A' && c <= 'F')
			{
				val = val * 16 + c - 'A' + 10;
			}
			else
			{
				return val * sign;
			}
		}
	}

	// decimal
	while (1)
	{
		c = *str;
		str++;

		if (c < '0' || c > '9')
		{
			return sign * val;
		}

		val = val * 10 + c - '0';
	}
}

int32 Q_strcmp(uint8 *s1, uint8 *s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
		{
			return 0;
		}

		++s1;
		++s2;
	}

	return ((*s1 < *s2) ? -1 : 1);
}

void Q_strcpy(uint8 *dest, uint8 *src)
{
	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = 0;
}

int32 Q_strlen(uint8 *str)
{
	int32 count = 0;

	while (str[count])
	{
		++count;
	}

	return count;
}

void Q_strncpy(uint8 *dest, uint8 *src, int32 count)
{
	if (count < 0)
	{
		return;
	}

	while (*src && count)
	{
		*dest++ = *src++;
		--count;
	}

	while (count)
	{
		*dest++ = 0;
		--count;
	}
}
