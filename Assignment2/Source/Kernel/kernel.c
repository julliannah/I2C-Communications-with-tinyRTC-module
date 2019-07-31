#include "i2c.h"
#include "stdio.h"
#include "stdlib.h"


void kernel_main() {
    uart_init();
    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing\n");
    puts("------------------------------------------------------------\n");
    puts("Assessment Group: 11\n");
    puts("S3695516: Le Quang Hien\n");
    puts("S3687637: Nguyen Nguyen Ha Nhan\n");
    puts("S3681447: Mai Duc Minh\n");
    char buf[50];
    while(1) {
        puts("\n");
        gets(buf, 50);
        puts(buf);
    }
}

