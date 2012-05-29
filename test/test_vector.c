#include <stdio.h>

#include "test_vector.h"

int main()
{
    vector_t v;
    int i;
    vector_t_init(&v);
    for (i = 0; i < 10; i++) {
        v.push_back(&v, i);
    }
    printf("v.size = %d\n", v.size(&v));
    for (i = 0; i < v.size(&v); i++) {
        printf("v[%d] = %d\n", i, v.at(&v, i));
    }
    v.update(&v, 3, 90);
    printf("now, v[3] = %d\n", v.at(&v, 3));
    v.clear(&v);
    printf("now, v.size = %d\n", v.size(&v));
    v.destroy(&v);
    return 0;
}

