# MultiCharDev
Example of creating a cluster of character devices driver in Linux. Tested on kernel 4.1.15

Usage:  
1. first copy the files to your local machine by  
    $> git clone https://github.com/georgewayne/MultiCharDev  
2. compile with make. if all goes well, you'll have kernel module named multi.ko  
    $> make  
3. use below command to monitor the kernel massages  
    $> tail -f /var/log/kern.log  
4. install the compiled kernel module. if sucessful, you'll see your new devices /dev/mydevname?.  
    $> sudo insmod multi.ko  
5. run the test program  
    $> sudo ./test  
6. try all choices (open, read, write, close) and exit the test program  
7. remove the kernel module  
    $> sudo rmmod multi  

A sample log from /var/log/kern.log is below:

Jan 24 22:41:46 raspberrypi kernel: [98038.140842] mydevname0 sucessfuly created  
Jan 24 22:41:46 raspberrypi kernel: [98038.141076] mydevname1 sucessfuly created  
Jan 24 22:41:46 raspberrypi kernel: [98038.141273] mydevname2 sucessfuly created  
Jan 24 22:41:46 raspberrypi kernel: [98038.141287] all 3 devices sucessfuly created  
Jan 24 22:42:08 raspberrypi kernel: [98059.808933] Driver: open() device /dev/mydevname0  
Jan 24 22:42:19 raspberrypi kernel: [98071.319973] Driver: read() device /dev/mydevname0  
Jan 24 22:42:25 raspberrypi kernel: [98077.147588] Driver: write() device /dev/mydevname0  
Jan 24 22:42:47 raspberrypi kernel: [98099.074007] Driver: open() device /dev/mydevname1  
Jan 24 22:42:50 raspberrypi kernel: [98102.136020] Driver: read() device /dev/mydevname1  
Jan 24 22:42:51 raspberrypi kernel: [98103.491231] Driver: write() device /dev/mydevname1  
Jan 24 22:43:18 raspberrypi kernel: [98130.193675] Driver: open() device /dev/mydevname2  
Jan 24 22:43:21 raspberrypi kernel: [98132.636033] Driver: read() device /dev/mydevname2  
Jan 24 22:43:21 raspberrypi kernel: [98133.130868] Driver: write() device /dev/mydevname2  
Jan 24 22:43:49 raspberrypi kernel: [98161.323873] Driver: close() device /dev/mydevname0  
Jan 24 22:44:21 raspberrypi kernel: [98193.476500] Driver: close() device /dev/mydevname1  
Jan 24 22:44:31 raspberrypi kernel: [98202.692468] Driver: close() device /dev/mydevname2  
Jan 24 22:44:48 raspberrypi kernel: [98219.888206] mydevname0 unregistered  
Jan 24 22:44:48 raspberrypi kernel: [98219.888382] mydevname1 unregistered  
Jan 24 22:44:48 raspberrypi kernel: [98219.888543] mydevname2 unregistered  
Jan 24 22:44:48 raspberrypi kernel: [98219.888594] all 3 devices unregistered

