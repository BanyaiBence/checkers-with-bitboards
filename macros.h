
#ifndef MACROS_H
#define MACROS_H

#define FOREACH(i, A) for(int _keep=1, \
_count=0,\
_size=sizeof (A) / sizeof *(A); \
_keep && _count != _size; \
_keep = !_keep, _count++) \
for(i = (A)+_count; _keep; _keep = !_keep)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define LOG(x, fmt, ...)    if(x){printf("%s@%d: " fmt "\n",\
__FILE__, __LINE__,__VA_ARGS__);}

#define MAIN()  int main (int argc, const char **argv)

#define NOW     time(NULL)

#define STRLITLEN(S)  (ARRAY_SIZE(S) - 1)

#define STRING char*

#define CAT(str1,str2)      (str1 "" str2)

#define ERROR(fmt, ...) fprintf(stderr, "Error: %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)

#define DIE exit(0)

#define SHIFT(bits, n) (n > 0 ? bits << n : bits >> -n)

#define SET_SHIFT(bits, n) (bits = (n > 0 ? bits << n : bits >> -n))

#define UNION(x, y) (x | y)

#define SET_UNION(x, y) (x |= y)

#define INTERSECT(x, y) (x & y)

#define SET_INTERSECT(x, y) (x &= y)

#define DIFFERENCE(x, y) (x & ~y)

#define SET_DIFFERENCE(x, y) (x &= ~y)

#define XOR(x, y) (x ^ y)

#define SET_XOR(x, y) (x ^= y)

#define NOT(x) (~x)

#define SET_NOT(x) (x = ~x)

#define ADD_STR(str, buff, idx, ...) (idx += sprintf(buff + idx, str, __VA_ARGS__));

#endif //MACROS_H
