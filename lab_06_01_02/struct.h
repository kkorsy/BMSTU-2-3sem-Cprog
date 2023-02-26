#ifndef __STRUCT_H__
#define __STRUCT_H__

#define LEN_MAX 25

struct object
{
    char name[LEN_MAX + 1];
    double mass;
    double volume;
};

#endif