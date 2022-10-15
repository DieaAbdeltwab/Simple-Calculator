#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(num,bit) num=num|(1<<bit)
#define ClER_BIT(num,bit) num=num&(~(1<<bit))
#define GET_BIT(num,bit) (num >> bit) & 0x01
#define TOOGLE_BIT(num,bit)  num=num^(1<<bit)



#endif