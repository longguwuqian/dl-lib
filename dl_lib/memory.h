#ifndef _DL_COMMON_DL_COMMON_H
#define _DL_COMMON_DL_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define IN
#define OUT

#define CHECK_MALLOC(ptr) do { \
        if(NULL == ptr) { \
                fprintf(stderr,"LINE %d:内存分配失败!\n",__LINE__); \
                exit(EXIT_FAILURE); \
        } \
}while (0)

#define min(x,y) ({ \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        (void)(&_x == &_y); \
        _x<_y?_x:_y;})

#define max(x,y) ({ \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        (void)(&_x == &_y); \
        _x<_y?_x:_y;})

static inline int same_sign_int(int a,int b)
{
        return !(((a^b) & INT_MIN) && (a&&b));
}

static inline void min_int_2(int array[],int len,int *min,int *min_2)
{
        int i;

        for(i = 0; i < len; i++) {
                *min = *min_2 = array[i];
                break;
        }
        for(i++; i < len; i++) {
                *min_2 = array[i];
                break;
        }
        if(*min > *min_2) {
                *min^=*min_2;
                *min_2^=*min;
                *min^=*min_2;
        }
        for(i++; i < len; i++) {
                if(array[i] < *min)
                        *min = array[i];
                else if(array[i] <= *min_2)
                        *min_2 = array[i];
        }
}

static inline void STDIN_FLUSH()
{
        static int c;
        while((c = getchar())!='\n'&&c != EOF);
}

static inline int user_says_yes()
{
        static char ans[5];
        while(1) {
                scanf("%4s",ans);
                __stdin_flush();
                if( ans[3] == '\0'                   &&
                    (ans[2] == 's' || ans[2] == 'S') &&
                    (ans[1] == 'e' || ans[1] == 'E') &&
                    (ans[0] == 'y' || ans[0] == 'Y')  ) return 1;
                if( ans[2] == '\0'                   &&
                    (ans[1] == 'o' || ans[1] == 'O') &&
                    (ans[0] == 'n' || ans[0] == 'N')  ) return 0;
        }
}


static inline void swap_i(int *a,int *b)
{
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
}

static inline int max_i(int array[],int length)
{
        int max = array[--length];
        while(length--) {
                if(array[length] > max) max = array[length];
        }
        return max;
}

static inline int min_i(int array[],int length)
{
        int min = array[--length];
        while(length--) {
                if(array[length] < min) min = array[length];
        }
        return min;
}

#endif
