// 2 image caches, sqrt17 table : 2360ms
// 1 image caches, sqrt17 table : 3094ms
// 1 image caches, sqrt17 table, sqr table : 2927ms

#include <stdio.h>
#include "il2212.h"
#include "images-32x32.h"
#include <string.h>
#include <stdint.h>

    #include <system.h>
    #include <sys/alt_timestamp.h>
    alt_u32 time[6];

    void printDouble(double a){
        if(a>=10000){
            alt_putstr("<big value>");
            return;
        }
        a/=1000;
        int i=0;
        for(i=0; i<4; i++){
            alt_putchar(((int)a)%10+'0');
            a*=10;
        }
        alt_putchar('.');
        for(i=0;i<2;i++){
            alt_putchar(((int)a)%10+'0');
            a*=10;
        }
    }
    void start_timer(){
        if (alt_timestamp_start() < 0) alt_putstr("No timestamp device.");
        time[0] = alt_timestamp();
    }

    void get_time(int i){
        time[i] = alt_timestamp();
    }

    void print_time(){
        alt_putstr("\nTotal time is");
        printDouble((double)(time[1] - time[0]) * 1000 / alt_timestamp_freq());
        alt_putchar('ms!\n');
    }
#ifdef DEBUG
#define pchar(x) alt_putchar(x)
#define pstr(x) alt_putstr(x)

#else
#define pchar(x)
#define pstr(x)
#endif

void printAscii_16(uint8_t* img, int x, int y){
    char asciiChars[] = {' ','.',':','-','=','+','/','t','z','U','w','*','0','#','%','@'};
    int i, j;
    for (i = 0; i < y; i++){
        for (j = 0; j < x; j++){
            alt_putchar(asciiChars[img[i*x+j]]);
        }
        alt_putchar('\n');
    }
}

int main(){

    alt_putstr("Hello from cpu_0!\n");

    int i = 0;
    // Initialize

    for (i = 0; i < 1020; i++){
        SQR_TABLE[i] = i*i;
    }
    MOORE[0] = 255;
    MOORE[1] = 255;
    MOORE[2] = 255;

    CPU1_STATE = 255;
    CPU2_STATE = 255;
    CPU3_STATE = 255;
    CPU4_STATE = 255;

    //wait for cpus start
    while(CPU1_STATE != 0 || CPU2_STATE != 0 || CPU3_STATE != 0 || CPU4_STATE != 0) delayabit();

    // Main loop
    uint8_t cur_image = 0;
    uint8_t *img;

    i = 0;

    start_timer();

    while (i < 75){  // 75 * 4 = 300 imgs
        alt_putstr(".");
        // send image to cpu1
        pstr("send image to cpu1, img=");
        pchar(cur_image+'0');
        pchar('\n');
        img = image_sequence[cur_image];
        img += 3;
        memcpy(IMAGE_CACHE_1, img, 3072);
        CPU1_STATE = 1;

        //wait cpu1 read ok
        while(CPU1_STATE == 1) delayabit();
        //send image to cpu2
        cur_image ++;
        pstr("send image to cpu2, img=");
        pchar(cur_image+'0');
        pchar('\n');
        img = image_sequence[cur_image];
        img += 3;
        memcpy(IMAGE_CACHE_1, img, 3072);
        CPU2_STATE = 1;

        //wait cpu1 read ok
        while(CPU2_STATE == 1) delayabit();
        //send image to cpu3
        cur_image ++;
        pstr("send image to cpu3, img=");
        pchar(cur_image+'0');
        pchar('\n');
        img = image_sequence[cur_image];
        img += 3;
        memcpy(IMAGE_CACHE_1, img, 3072);
        CPU3_STATE = 1;

        //wait cpu2 read ok
        while(CPU3_STATE == 1) delayabit();
        //send image to cpu4
        cur_image ++;
        pstr("send image to cpu4, img=");
        pchar(cur_image+'0');
        pchar('\n');
        img = image_sequence[cur_image];
        img += 3;
        memcpy(IMAGE_CACHE_1, img, 3072);
        CPU4_STATE = 1;

        cur_image ++;
        if (cur_image > 7) cur_image = 0;

        //wait for result
        while(CPU1_STATE != 3 || CPU2_STATE != 3 || CPU3_STATE != 3 || CPU4_STATE != 3) delayabit();

        pstr("start correct+sobel\n");
        // start correct+sobel
        CPU1_STATE = 4;
        CPU2_STATE = 4;
        CPU3_STATE = 4;
        CPU4_STATE = 4;
        //wait for result
        while(CPU1_STATE != 5 || CPU2_STATE != 5 || CPU3_STATE != 5 || CPU4_STATE != 5) delayabit();

        MOORE[0] = HMAX_4 - HMIN_4;
        MOORE[1] = HMAX_3 - HMIN_3;
        MOORE[2] = HMAX_2 - HMIN_2;

#ifdef DEBUG
        printf("OK!\n");
        printf("1\n");
        printAscii_16(CPU1_RESULT,14,14);
        printf("2\n");
        printAscii_16(CPU2_RESULT,14,14);
        printf("3\n");
        printAscii_16(CPU3_RESULT,14,14);
        printf("4\n");
        printAscii_16(CPU4_RESULT,14,14);
#endif
        i++;
    }
    get_time(1);
    print_time();
    return 0;
}
