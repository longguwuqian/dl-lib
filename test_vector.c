#include <stdio.h>

#include "dl_lib/dl_vector.h"
#include "dl_lib/dl_stack.h"

DL_VECTOR_TEMPLATE(vector_t, int)

int main()
{
    DL_VECTOR(vector_t, v)
    int i;
    DL_VECTOR_INIT(vector_t, &v)
    for (i = 0; i < 10; i++) {
        v.push_back(&v, i);
    }
    printf("v.size = %d\n", v.size(&v));
    for (i = 0; i < v.size(&v); i++) {
        printf("v[%d] = %d\n", i, v.at(&v, i));
    }
    v.clear(&v);
    printf("now, v.size = %d\n", v.size(&v));
    v.destroy(&v);
    return 0;
}

