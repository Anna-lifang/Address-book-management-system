
#include "sys/alt_stdio.h"
typedef unsigned char uint8_t;

#define SHARED_BASE         0x102000
#define ONCHIP_BASE         0x2020

#define IMAGE               ((uint8_t*)(0x3400))
//#define RESULT_IMAGE        ((uint8_t*)(ONCHIP_BASE + 0xc00))

#define IMAGE_CACHE_1       ((uint8_t*)(SHARED_BASE + 0x000))
#define IMAGE_CACHE_2       ((uint8_t*)(SHARED_BASE + 0x1000)) //  \  use one of them
#define SQR_TABLE           ((int*)(SHARED_BASE + 0x1000)) //      /


#define VARIBLE_BASE        (SHARED_BASE + 0x0c00)
#define HMAX_1              (*(uint8_t*)(VARIBLE_BASE + 0x000))
#define HMIN_1              (*(uint8_t*)(VARIBLE_BASE + 0x001))
#define HMAX_2              (*(uint8_t*)(VARIBLE_BASE + 0x002))
#define HMIN_2              (*(uint8_t*)(VARIBLE_BASE + 0x003))
#define HMAX_3              (*(uint8_t*)(VARIBLE_BASE + 0x004))
#define HMIN_3              (*(uint8_t*)(VARIBLE_BASE + 0x005))
#define HMAX_4              (*(uint8_t*)(VARIBLE_BASE + 0x006))
#define HMIN_4              (*(uint8_t*)(VARIBLE_BASE + 0x007))
#define MOORE               ((uint8_t*)(VARIBLE_BASE + 0x008))  //Stack MOORE[3]
// cpu1 use moore0-2
// cpu2 use moore0-1 + hmax1-hmin1
// cpu3 use moore0 + hmax1-hmin1 + hmax2-hmin2
// cpu4 use hmax-hmin(1-3)
//after calc:
// cpu0: moore0 <- hmax4-hmin4
//       moore1 <- hmax3-hmin3
//       moore2 <- hmax2-hmin2

#define STATE_BASE          (SHARED_BASE + 0x0d00)
#define CPU1_STATE          (*(uint8_t*)(STATE_BASE + 0x000))
#define CPU2_STATE          (*(uint8_t*)(STATE_BASE + 0x001))
#define CPU3_STATE          (*(uint8_t*)(STATE_BASE + 0x002))
#define CPU4_STATE          (*(uint8_t*)(STATE_BASE + 0x003))
#define CPU1_IMAGE          (*(uint8_t*)(STATE_BASE + 0x004)) //image seq. [0-7]
#define CPU2_IMAGE          (*(uint8_t*)(STATE_BASE + 0x005))
#define CPU3_IMAGE          (*(uint8_t*)(STATE_BASE + 0x006))
#define CPU4_IMAGE          (*(uint8_t*)(STATE_BASE + 0x007))

#define RESULT_BASE         (SHARED_BASE + 0x0e00)
#define CPU1_RESULT         ((uint8_t*)(RESULT_BASE + 0x000))
#define CPU2_RESULT         ((uint8_t*)(RESULT_BASE + 0x100))
#define CPU3_RESULT         ((uint8_t*)(RESULT_BASE + 0x200))
#define CPU4_RESULT         ((uint8_t*)(RESULT_BASE + 0x300))

extern void delay (int millisec);
#define D(a)
#define delayabit() delay(1)
#define abs(a) ((a)<0?(-(a)):(a))
