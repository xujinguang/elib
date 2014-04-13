#ifndef _LIB_BIT_H_
#define _LIB_BIT_H_

/*Author: xujinguang
 *Email:xu_jin_guang@gmail.com
 *Create Date:2014.4.7
 *CopyLeft: GPL2.0
 */

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/*To test an unsigned int/long integer is the nth power of 2
 if x is the n power of 2, so There is only one bit that is 1 in x
      x = 0001 0000
    x-1 = 0000 1111
 x&(x-1)= 0000 0000
 if the value ofx&(x-1) is zero, so x is the n pow of 2,else is no!*/
#define IS_P2N(x) (((x) & ((x) - 1)) == 0 ? 1 : 0)

/*To test x is 2^n-1? let x = y + 1.so x&(x-1)=(y+1)&y, that's all!*/
#define IS_P2N_SUB_ONE(x) (((x) & ((x) + 1)) == 0 ? 1 : 0)
#define IS_P2N_ADD_ONE(x) IS_P2N((x) - 1) /*(x - 1)&(x - 2) */

#define RIGHT_FIRST_ONE(x) ((x) & -(x))
#define RIGHT_FIRST_ZERO(x) (~(x) & ((x) + 1))

/* * ~(x | -x) or (x & -x) -1*/
#define SUFFIX_ZERO_MASK(x) (~(x) & ((x) - 1))

/*the right one bit and the surffix zero*/
#define SUFFIX_ONE_ZERO_MASK(x) ((x) ^ ((x) - 1))

/*reverse the surffix zeroi, if x = 0, then the value bits are all one*/
#define SUFFIX_ZERO_REVERSE(x) ((x) | ((x) - 1))

/*set the right zero bit to one*/
#define set_right_bit ((x) | ((x) + 1))

/*set the right one bit to zero*/
#define put_right_bit(x) ((x) & ((x) - 1))

/*the right bit is 0?*/
#define IS_LEFT_ZERO(x) ((-(x) & ((x) + 1)) = 0 ? 0 : 1)
#define IS_LEFT_ONE(x) !IS_LEFT_ZERO(x)

#define swap_bits(x, y, m) {\
    int _t; _t = (x ^ y) & m; x ^= _t; y ^= _t;}
   /* (x) = (x) ^ (y); (y) = (y) ^ ((x) & m); (x) = (x) ^ (y);}*/

#define exchange_bits(x, p1, p2, m) {\
    int _t1, _t2;\
    _t1 = x ^ (x >> ((p2) - (p1))) & m;\
    _t2 = _t1 << ((p2) - (p1));\
    x = x ^ _t1 ^ _t2;}

/*The population count */
static char pop_table[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

#define pop(x) pop_table[(x) & 0xFF] +\
               pop_table[((x) >> 8) & 0xFF] +\
               pop_table[((x) >> 16) & 0xFF] +\
               pop_table[(x) >> 24]

unsigned int pop1(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    x += x >> 16;
    return x & 0x0000003F;
}

unsigned int pop2(unsigned int x)
{
    unsigned int n;
    
    n = (x >> 1) & 0x77777777;
    x -= n;
    n = (x >> 1) & 0x77777777;
    x -= n;
    n = (x >> 1) & 0x77777777;
    x -= n;
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x *= 0x01010101; /*the sum of four byte*/

    return x >> 24;
}

/*the sparse population count*/
unsigned int pop3(unsigned int x)
{
    unsigned int n = 0;

    while(x)
    {
        x &= x - 1;
        ++n;
    }
    return n;
}

/*pop(x) = x - x>>1 - x>>2 -...-x>>31*/
unsigned int pop4(unsigned int x)
{
    unsigned int n;

    n = x;
    while(x)
    {
        x >>= 1;
        n -= x;
    }

    return n;
}
#ifdef X86_64
unsigned int pop64(unsigned int x)
{
    unsigned long long n;

    n = x * 0x0002000400080010ULL;
    n &= 0x1111111111111111ULL;
    n *= 0x1111111111111111ULL;
    return n >> 60;
}
#endif

unsigned int pop_array(unsigned int *pop, int n)
{
    int i, j, min_val;
    unsigned int s, s8, x;

    s = 0;
    for(i = 0; i < n; i += 31) {
        min_val = min(n, i + 31);
        s8 = 0;
        for(j = i; j < min_val; ++j) {
            x = pop[j];
            x -= ((x >> 1) & 0x55555555);
            x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
            x = (x + (x >> 4)) & 0x0F0F0F0F;
            s8 += x;
        }
        x = (s8 & 0x00FF00FF) + ((s8 >> 8) & 0x00FF00FF);
        x = (x & 0x0000FFFF) + (x >> 16);
        s += x;
    }

    return s;
}

/*parity checking - those methods are faster than iterative method*/
unsigned char parity_table[256] = {
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
};
#define parity(x) parity_table[x]

unsigned int parity0(unsigned int x)
{
    unsigned p;

    p = x ^ (x >> 1);
    p ^= p >> 2;
    p ^= p >> 4;
    p ^= p >> 8;
    p ^= p >> 16;

    return p & 0x1;
}

unsigned int parity1(unsigned int x)
{
    x ^= x >> 1;
    x = (x ^ (x >> 2)) & 0x11111111;
    x *= 0x11111111;    //add /each 
    return (x >> 28) & 0x1;
}

/*the leading- zero count*/
unsigned int leading_zero_num(unsigned int x)
{
    unsigned int nr;
    
    if(x == 0)
        return 32;
    nr = 0;
    if(x <= 0x0000FFFF) {
        nr += 16;
        x <<= 16;
    }
    if(x <= 0x00FFFFFF) {
        nr += 8;
        x <<= 8;
    }
    if(x <= 0x0FFFFFFF) {
        nr += 4;
        x <<= 4;
    }
    if(x <= 0x3FFFFFFF) {
        nr += 2;
        x <<= 2;
    }
    /*
    if( x <= 0x7FFFFFFF) {
        ++nr;
    } 优化*/
    nr = nr + 1 - (x >> 31);

    return nr;
}

unsigned int leading_zero_num1(unsigned int x)
{
    int nr;

    if(x == 0)
        return 32;

    nr = 0;
    if((x >> 16) == 0) {
        nr += 16;
        x <<= 16;
    }
    if((x >> 24) == 0) {
        nr += 8;
        x <<= 8;
    }
    if((x >> 28) == 0 ) {
        nr += 4;
        x <<= 4;
    }
    if((x >> 30) == 0) {
        nr += 2;
        x <<= 2;
    }
    nr = nr + 1 -  x >> 31;

    return nr;
}

unsigned int leading_zero_num2(unsigned int x)
{
    unsigned int y, nr;

    nr = 32;
    y = x >> 16;
    if(y) {
        nr -= 16;
        x = y;
    }
    y = x >> 8;
    if(y) {
        nr -= 8;
        x = y;
    }
    y = x >> 4;
    if(y) {
        nr -= 4;
        x = y;
    }
    y = x >> 2;
    if(y) {
        nr -= 2;
        x = y;
    }
    y = x >> 1;
    if(y) 
        return nr - 2;
    return nr - x;
}

unsigned int leading_zero_num3(unsigned int x)
{
    unsigned int y;
    unsigned int nr, c;
    
    nr = 32;
    c = 16;
    do {
        y = x >> c;
        if(y) {
            nr -= c;
            x = y;
        }
        c >>= 1;
    }while(c);
    return nr - x;
}


unsigned int leading_zero_num4(unsigned int x)
{
    unsigned int nr;

    if(x == 0)
        return 32;
    nr = 0;
    while((int)x > 0) {
        ++nr;
        x <<= 1;
    }
    return nr;
}

unsigned int leading_zero_num5(unsigned int x)
{
    unsigned int nr;
    if(x == 0)
        return 32;
    nr = 0;
    while(x) {
        ++nr;
        x >>= 1;
    }
    return 32 - nr;
}


unsigned int leading_zero_num6(unsigned int x)
{
    int y, m;
    unsigned int nr;

    y = -(x >> 16);
    m = (y >> 16) & 16;
    nr = 16 - m;
    x >>= m;

    y = x - 0x100;
    m = (y >> 16) & 8;
    nr += m;
    x <<= m;

    y = x - 0x1000;
    m = ( y >> 16) & 4;
    nr += m;
    x <<= m;

    y = x - 0x4000;
    m = ( y >> 16) & 2;
    nr += m;
    x <<= m;

    y = x >> 14;
    m = y & ~(y >> 1);
    return nr + 2 - m;
}


unsigned int leading_zero_num7(unsigned int x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return pop(~x);
}

#define LE 0
unsigned int leading_zero_num8(unsigned int x)
{
    union{
        unsigned int as_int[2];
        double as_double;
    } y;
    unsigned int nr;

    nr = 0;
    y.as_double = (double)x + 0.5; //-
    nr = 1054 - (y.as_int[LE] >> 20);
                                   //+ nr=(nr&31)+(nr>>9)
    return nr;
}

unsigned int leading_zero_num9(unsigned int x)
{
    union{
        unsigned int as_int;
        double as_float;
    } y;
    unsigned int nr;

    nr = 0;
    x = x & ~(x >> 1);
    y.as_float = (float)x + 0.5f; //-
    nr = 158 - (y.as_int >> 23);
                                   //+ nr=(nr&31)+(nr>>6)
    return nr;
}

#define leading_zero_num10(x) (31 - log(2, (x)))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_PER_BYTE           8
#define BITS_TO_LONGS(nr)       DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define BITS_TO_U64(nr)         DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(u64))
#define BITS_TO_U32(nr)         DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(u32))
#define BITS_TO_BYTES(nr)       DIV_ROUND_UP(nr, BITS_PER_BYTE)

#define for_each_set_bit(bit, addr, size) \
	for ((bit) = find_first_bit((addr), (size));		\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

/* same as for_each_set_bit() but use bit as value to start with */
#define for_each_set_bit_from(bit, addr, size) \
	for ((bit) = find_next_bit((addr), (size), (bit));	\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))
#endif
