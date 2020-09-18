#ifndef _ERROR_CORRECTION_H_
#define _ERROR_CORRECTION_H_

#define BIT01_POS 0x3
#define BIT02_POS 0x5
#define BIT03_POS 0x6
#define BIT04_POS 0x9
#define BIT05_POS 0xA
#define BIT06_POS 0xC
#define BIT07_POS 0xE
#define BIT08_POS 0x7
#define BIT09_POS 0x1
#define BIT10_POS 0x2
#define BIT11_POS 0x4
#define BIT12_POS 0x8

#define POS00_BIT 0x0
#define POS01_BIT (1 << 0x8)
#define POS02_BIT (1 << 0x9)
#define POS03_BIT (1 << 0x0)
#define POS04_BIT (1 << 0xA)
#define POS05_BIT (1 << 0x1)
#define POS06_BIT (1 << 0x2)
#define POS07_BIT (1 << 0x7)
#define POS08_BIT (1 << 0xB)
#define POS09_BIT (1 << 0x3)
#define POS10_BIT (1 << 0x4)
#define POS11_BIT 0x0
#define POS12_BIT (1 << 0x5)
#define POS13_BIT 0x0
#define POS14_BIT (1 << 0x6)
#define POS15_BIT 0x0


uint16_t bit_pos_to_bit[16] = {
    POS00_BIT,
    POS01_BIT,
    POS02_BIT,
    POS03_BIT,
    POS04_BIT,
    POS05_BIT,
    POS06_BIT,
    POS07_BIT,
    POS08_BIT,
    POS09_BIT,
    POS10_BIT,
    POS11_BIT,
    POS12_BIT,
    POS13_BIT,
    POS14_BIT,
    POS15_BIT
};


#define ERROR_CORRECT(x) (((x) ^ bit_pos_to_bit[ \
                            (((((x) >> 0x0) & 1) * BIT01_POS) ^ \
                             ((((x) >> 0x1) & 1) * BIT02_POS) ^ \
                             ((((x) >> 0x2) & 1) * BIT03_POS) ^ \
                             ((((x) >> 0x3) & 1) * BIT04_POS) ^ \
                             ((((x) >> 0x4) & 1) * BIT05_POS) ^ \
                             ((((x) >> 0x5) & 1) * BIT06_POS) ^ \
                             ((((x) >> 0x6) & 1) * BIT07_POS) ^ \
                             ((((x) >> 0x7) & 1) * BIT08_POS) ^ \
                             ((((x) >> 0x8) & 1) * BIT09_POS) ^ \
                             ((((x) >> 0x9) & 1) * BIT10_POS) ^ \
                             ((((x) >> 0xA) & 1) * BIT11_POS) ^ \
                             ((((x) >> 0xB) & 1) * BIT12_POS))]) & 0xff)

#endif