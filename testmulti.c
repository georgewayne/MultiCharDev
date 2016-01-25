#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int currentdev = 0;
    char devname[256] = "/dev/mydevname0";
    int ret, fd0=0, fd1=0, fd2=0, *fd;
    int choice=0;
    size_t len=1;
    char str[256];
    while (choice != 6) {
        printf("\nPlease choose operation:\n\t1: read\n\t2: write\n\t3: open\n\t4: close\n\t5: next device\n\t6: exit this program\nYour choice(1~6): ");
        scanf("%[^\n]%*c", str);
        sscanf(str, "%d", &choice);
        printf("choice: %s -> %d\n", str, choice);
        switch (currentdev) {
            case 0:
                fd = &fd0;
                break;
            case 1:
                fd = &fd1;
                break;
            case 2:
                fd = &fd2;
                break;
        }
        switch(choice) {
            case 1: /*read*/
                if (*fd <= 0) {
                    printf("mydevname%d not open. Please first open the device\n", currentdev);
                    break;
                }
                ret = read(*fd, NULL, len);
                if (ret < 0) {
                    perror("Fail to read.\n");
                    return errno;
                }
                break;
            case 2: /*write*/
                if (*fd <= 0) {
                    printf("mydevname%d not open. Please first open the device\n", currentdev);
                    break;
                }
                ret = write(*fd, NULL, len);
                if (ret < 0) {
                    perror("Fail to write.\n");
                    return errno;
                }
                break;
            case 3: /*open*/
                if (*fd > 0) {
                    printf("mydevname%d already open.\n", currentdev);
                    break;
                }
                *fd = open(devname, O_RDWR);    //open with read/write
                if (*fd < 0) {
                    perror("Fail to open the device...");
                    return errno;
                }
                break;
            case 4: /*close*/
                if (*fd == 0) {
                    printf("Device already closed.\n");
                    break;
                }
                ret = close(*fd);
                if (ret < 0) {
                    perror("Device fail to close.\n");
                    return errno;
                }
                *fd = 0;
                break;
            case 5:
                currentdev = (currentdev + 1) % 3;
                sprintf(devname, "/dev/mydevname%d", currentdev);
                printf("Current device is %s\n", devname);
                break;
            case 6:
                return 0;
            default:
                break;
        }
    } /*while loop*/
    return 0;
}
