#include <linux/kd.h> //KDSETLED
#include <sts/ioctl.h>
#include <unistd.h> //sleep()

int main () {
    int keybitson = 0x7;

    int keybitsoff = 0x0;

    ioctl (1,KDSETLED,keybitson);

    sleep (1);

    ioctl (1,KDSETLED,keybitsoff);
}
