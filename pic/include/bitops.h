#ifndef _BITOPS_H_
#define _BITOPS_H_

#define toggle_bit(nr, addr) do{ addr ^= (1<<nr); }while(0)
#define set_bit(nr, addr) do{ addr |= (1<<nr); }while(0)
#define clear_bit(nr, addr) do{ addr &= !(1<<nr); }while(0)
#define test_bit(nr, addr) (( addr&(1<<nr) ))

#endif // _BITOPS_H_
