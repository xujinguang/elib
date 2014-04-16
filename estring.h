#ifndef _E_STRING_H_
#define _E_STRING_H_

#include <string.h>
#include <math.h>

#define CHECK_IN(patter, str) \
	if(pattern == NULL || str == NULL)\
		return NULL

/*Brute-force algorithm: The obvious method for pattern matching*/
const char* strsearch_bf(const char* pattern, const char* str)
{
	int i, j;
	int m, n;

	CHECK_IN(pattern, str);
	m = strlen(pattern);
	n = strlen(str);
	if(m > n)
		return NULL;

	i = j = 0;
	while(j < m && i < n)
	{
		if(str[i] == pattern[j])
		{
			++i;
			++j;
		}
		else
		{
			i -= j + 1;
			j = 0;
		}
	}

	if(j == m)
		return str + i - m;
	return NULL;
}

long  estrtol(const char* str, int len, int base)
{
	int i;
	long x;

	x = 0;
	for(i = 0; i < len; ++i)
		x = x * base + str[i];

	return x;
}

/*bstrtoi - convert binary string to int
 *@str	:	a string that consist by character 0/1 
 *@len	:	how many bytes to covert*/
int bstrtoi(const char* str, int len)
{
	int val = 0;
	int i = 0;

	if(str == NULL || len == 0)
		return -1;
	
	while(i < len)
		val = (val << 1) + str[i++] - '0';

	return val;
}

/*rksearch2 - Rabin-Karp algorithm that base = 2*/
const char* bstrsearch_rk(const char* pattern, const char* str)
{
	int pattern_hash, str_hash;
	int h;
	int n, m;
	int i;

	CHECK_IN(pattern, str);

	m = strlen(pattern);
	n = strlen(str);
	if(m > n)
		return NULL;

	h = 1 << (m -1);
	pattern_hash = bstrtoi(pattern, m);
	str_hash = bstrtoi(str, m);

	for(i = 0; i < n - m + 1; ++i)
	{
		if(pattern_hash == str_hash && 
				!strncmp(pattern, str + i, m))
			return str + i;

		if(str[i] - '0')
			str_hash = ((str_hash - h) << 1) + str[i + m] - '0';
		else
			str_hash = (str_hash << 1) + str[i + m] - '0';
	}

	return NULL;
}

/*__rksearch: Rabin-Karp algorithm
  @pattern 	: search pattern
  @str		: string to search
  @base		: to calculate the hash value
  @prime	: a big prime to use mod
 */
static const char* __rksearch(const char* pattern, const char* str,  
		int base, int prime)
{
		long pattern_hash, str_hash;
		long high;
		int m, n;
		int i; 
	
		m = strlen(pattern);
		n = strlen(str);
		high = pow(base, m - 1);
		high = high % prime; 
		pattern_hash = estrtol(pattern, m, base) % prime;
		str_hash = estrtol(str, m, base) % prime; 

		for (i = 0; i < n - m + 1; ++i) {
			if (pattern_hash == str_hash && 
					!strncmp(pattern, str + i, m))
				return str + i;

			str_hash = ((str_hash - str[i] * high) * base + str[i + m]) % prime;
		} 

		return NULL;
}

static const char* strsearch_rk(const char *pattern, const char *str)
{
	CHECK_IN(pattern, str);

	if(strlen(pattern) > strlen(str))
		return NULL;

	/*prime number: 2^31-1 = 2147483647; 2^19-1=524287*/
	return __rksearch(pattern, str, 2, 524287);
}

/*shift or algorithm*/

#define ALPHER_SPACE_SIZE   256
#define DWORD   (sizeof(unsigned int) * 8)
static const char * strsearch_so(const char* pattern, const char* str)
{
    unsigned int limit, j;
    unsigned int s[ALPHER_SPACE_SIZE];
    int i;
    int m, n;

    CHECK_IN(pattern, str);
    m = strlen(pattern);
    n = strlen(str);
    if(m > DWORD || m > n)
        return NULL;

    /*init s array*/
    for(i = 0; i < ALPHER_SPACE_SIZE; ++i)
        s[i] = 0xFFFFFFFF;
    for(i = 0, j = 1; i < m; ++i, j <<= 1)
        s[pattern[i]] &= ~j;

    limit = ~((1 << m) - 1);
    
    for(j = ~0, i = 0; i < n; ++i)
    {
        j = (j << 1) | s[str[i + 1]];
        if(j < limit)
            return str + i - m + 1;
    }

    return NULL;
}

static inline void init_next(const char *pattern, int *next)
{
	int i, j;
	
	i = j = -1;
	next[0] = -1;
	while(i < strlen(pattern))
	{
		if(j == -1 || pattern[i] == pattern[j])
		{
			++j;
			++i;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

/* Knuth-Morris-Pratt string matching algorithm*/
static const char* strsearch_kmp(const char *pattern, const char *str)
{
	int i, j;
	int m, n;
	int *next;

	CHECK_IN(pattern, str);
	m = strlen(pattern);
	n = strlen(str);
	if(m > n)
		return NULL;

	next = malloc(m << 2);
	if(next == NULL)
		return NULL;
	init_next(pattern, next);

	i = j = -1;
	while(i < n && j < m)
	{
		if(j == -1 || str[i] == pattern[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}

	if(j == m)
		return str + i - m;

	return NULL;
}

enum{
	STRING_SEARCH_KMP,	
	STRING_SEARCH_RK,
	STRING_SEARCH_BF,		
};

static const char* (*search_fun[])(const char* pattern, const char* str) = {
	strsearch_kmp,
	strsearch_rk,
	strsearch_bf};

#define strsearch(PATTERN, STR, ID)	(search_fun[ID](PATTERN, STR))
#endif
