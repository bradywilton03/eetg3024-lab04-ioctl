/*
 * Name: Brady Wilton
 * Date: 02/03/26
 * Program: Linux Binary Keyboard LED Output
 * Description:
 *  Input a decimal number between 0 and 7, and watch as the num lock, caps lock and scroll lock LEDs display the corresponding binary code.
 */

#include <linux/kd.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define SCANFSUCCESS 1
#define LOWERLIMIT 0
#define UPPERLIMIT 7
#define LSB 1
#define SECONDSB 2
#define MSB 4
#define RESET   0

int main(void)
{
    int displayValue;
    int displayMask = FALSE;
    int b0;
    int b1;
    int b2;

    while (TRUE) {
        printf("\nWhat is a number between 0 and 7?\n\n");
        fflush(stdout);

        /*Filter out non-numeric characters.*/
        if (scanf("%d", &displayValue) != SCANFSUCCESS) {
            printf("\nERROR - That was not an integer.\n\n");

            /*This prevents infinite error messages from continuously printing.*/
            while (getchar() != '\n');

            continue;
        }

        /*Filter out illegal numeric values.*/
        if (displayValue < LOWERLIMIT || displayValue > UPPERLIMIT) {
            printf("\nERROR - That was not an integer between 0 and 7.\n\n");

            continue;
        }

        break;
    }

    /*Implement bit shifting and masking to store bits as LSBs in corresponding integers.*/
    b0 = (displayValue >> 0) &TRUE;
    b1 = (displayValue >> 1) &TRUE;
    b2 = (displayValue >> 2) &TRUE;

    /*Implement weights on the final integer value, which will be applied directly to the keyboard LEDs in the specified pattern.*/
    if (b1) displayMask |= MSB;
    if (b2) displayMask |= SECONDSB;
    if (b0) displayMask |= LSB;

    /*Apply masking to LEDs.*/
    ioctl(1, KDSETLED, displayMask);

    printf("\nPress ENTER to exit.\n");
    fflush(stdout);

    /*Prevent immediate program exit.*/
    while (getchar() != '\n');
    getchar();

    ioctl(1, KDSETLED, RESET);

    return 0;
}
