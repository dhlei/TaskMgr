#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
    char name[20];
    unsigned long size;
    char unit[20];
}MEMORY_INFO;

typedef struct
{
    double total;
    double use_rate;
}MEMORY_PACK;

MEMORY_PACK *get_memory_info();

#ifdef __cplusplus
}
#endif
