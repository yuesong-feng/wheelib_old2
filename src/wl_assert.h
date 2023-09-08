#ifndef WL_ASSERT_H
#define WL_ASSERT_H

#define wl_assert(x)    \
do {    \
    if (!(x)) \
        exit(-1);\
} while(0)



#endif
