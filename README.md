## About
```
d8b   db d88888b .d8888.  .o88b.  .d8b.    NESCA4 - Многопоточный linux сканер портов,
888o  88 88'     88'  YP d8P  Y8 d8' `8b   с точностью nmap-а, обработкой nesca3 брутфорсом
88V8o 88 88ooooo `8bo.   8P      88ooo88   самых популярных протоколов и сканированием DNS.
88 V8o88 88~~~~~   `Y8b. 8b      88~~~88    
88  V888 88.     db   8D Y8b  d8 88   88   Был сделан с вдохновением от nesca3 & nmap.
VP   V8P Y88888P `8888Y'  `Y88P' YP   YP   by oldteam & lomaster.
```
```
PS: Перечислять все возможности тут я не буду. Прочитать о том что умеет nesca4 и
как это разрабатывалось читайте в resources/do_not_read.txt
```

**Debian 12:**  
```
sudo apt-get install libcurl4-openssl-dev nodejs
sudo apt install gcc g++ make git cmake libssh-dev
git clone https://github.com/oldteamhost/nesca4
cd nesca4
cmake .
make -j12
```

**Arch 2023:**  
```
sudo pacman -S curl cmake nodejs
git clone https://github.com/oldteamhost/nesca4
cd nesca4
cmake .
make -j12
```

**Screenshots not save!**
```
cd nesca4 && sudo chmod u+rwx,g+r,o+r utils/ 
```

Для компиляции без библиотек, нужно зайти в файл `config/compile.h`, и закомментировать, или удалить строчку отвечающую за библиотеку, без которой вы хотите скомпилировать:

``` с++
#define HAVE_CURL
#define HAVE_SSH
#define HAVE_HIKVISION
#define HAVE_NODE_JS
```
