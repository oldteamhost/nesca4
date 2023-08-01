![alt text](https://i.imgur.com/YUaJEut.png)

## About
**NESCA4** - Многопоточный unix сканер портов, с точностью nmap-а, обработкой nesca3, и брутфорсом самых популярных протоколов и сканированием DNS.
Был сделан с вдохновением от ![nesca3](https://github.com/pantyusha/nesca) & ![nmap](https://github.com/nmap/nmap).  

Может сканировать методами: `SYN` `FIN` `XMAS` `NULL` `WINDOW` `ACK` `MAIMON`.  
Может выполнять пинг методами: `SYN` `ACK` `ICMPECHO` `ICMPINFO` `ICMPTIMESTAMP`.  
Может брутфорсить: `RVI` `HIKVISION` `BASICAUTH` `FTP` `SSH` `SMTP` `RTSP`.

**PS:** Перечислять все возможности тут я не буду. Прочитать о том что умеет nesca4 и как это разрабатывалось читайте в resources/do_not_read.txt

## Compilation
Я не заливаю код который не компилируется!
Если не выходит, значит у вас что-то не так с системой.

**Debian 11:**  
```
    sudo apt-get install libcurl4-openssl-dev
    sudo apt install g++ make git cmake libssh-dev
    git clone https://github.com/oldteamhost/nesca4
    cd nesca4
    cmake .
    make -j12
```

**Arch 2023:**  
```
    sudo pacman -S curl cmake
    git clone https://github.com/oldteamhost/nesca4
    cd nesca4
    cmake .
    make -j12
```
### non-lib
Для компиляции без библиотек, нужно зайти в файл `config/compile.h`, и закомментировать, или удалить строчку отвечающую за библиотеку, без которой вы хотите скомпилировать:

``` с++
#define HAVE_CURL
#define HAVE_SSH
#define HAVE_HIKVISION
```
