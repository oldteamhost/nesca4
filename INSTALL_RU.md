# Установка NESCA 4
Это не совсем установка, скорее компиляция из исходного кода, что может оказаться сложным если вы не делали это раньше.
Следите за каждым шагом очень внимательно, в идеале даже понимайте что на нем происходит.

## ЗАВИСИМОСТИ
В начале вам нужно установить необходимые зависимости, для успешной компиляции кода. Это компиляторы `gcc` и `g++`, утилита `make` и `git`.

**Для Arch linux выполните:**
```
sudo pacman -S git make gcc
```

**Для Debian linux выполните:**
```
sudo apt install build-essential git
```
Утилита `git` нужна для клонирования этого репозитория, соответственно исходного кода _nesca4_; `gcc`, `g++`, `make` для компиляции этого кода.

**PS:** Здесь перечислены команды для установки зависимостей лишь для двух систем, `arch` и `debian`, другие системы здесь отсутствуют, ведь эти другие
основаны на двух этих, скажем, если у вас `Kali` или `Ubuntu`, вам нужно использовать команды для `Debian`, если у вас, например, `Manjaro`, то команды для
`Αrch`.

## СКАЧИВАНИЕ
Теперь нам нужно загрузить исходный код _nesca4_, чтобы в дальнейшем его скомпилировать.

**Если вы установили (git) на предыдущем шаге, вы можете выполнить это:**
```
git clone https://github.com/oldteamhost/nesca4
```
**Но можно обойтись и без git, скачав zip-архив с github, и конечно, разархивировав его:**
```
- Открыть https://github.com/oldteamhost/nesca4
- Нажать на (<> CODE)
- Затем нажать на (Download ZIP)
- Разархивировать скачанный архив, например, с помощью (unzip).
```
**PS:** Этот способ более сложный, поскольку требует некоторых знаний терминала.

## КОНФИГУРАЦИЯ
Теперь наступает этап настройки, - конфигурации исходного кода и его компиляции.

**Для начала вам нужно зайти в директорию с кодом nesca4:**
```
cd nesca4
```
Обратите внимание, что директория `nesca4`, должна находиться в вашей текущей директории. Можете проверить это с помощью утилиты `ls`.

**Затем нужно запустить файл (configure):**
```
./configure
```

### ДРУГАЯ КОНФИГУРАЦИЯ
Этот шаг не обязателен, но иногда необходим. Помимо обычного вызова `configure`, как выше, можно вызвать его с определенными параметрами.

**Чтобы отключить библиотеку hikvision, запустите configure с опцией (--disable-hikvision):**
```
./configure --disable-hikvision
```
**Чтобы отключить библиотеку dvr, запустите configure с опцией (--disable-dvr):**
```
./configure --disable-dvr
```
**Также вы можете использовать их вместе:**
```
./configure --disable-dvr --disable-hikvision
```
## КОМПИЛЯЦИЯ
Теперь этап компиляции, после которого, вероятно, вы сможете использовать _nesca4_.

**Для компиляции выполните:**
```
make
```
**Процесс можно ускорить, если запустить компиляцию в потоках, опция (-j)**:
```
make -j
```
**PS:** Сначала будет компиляция `ncsock`, затем `nesca4`. В самом конце будет линковка всех файлов в исполняемый (программу `nesca4`).

## ЗАПУСК NESCA4
Если компиляция прошла успешно, и у вас невозникли ошибки при ней, - то у вас в текущей директории есть исполняемый файл `nesca4`, это и есть сама программа, она готова к использованию.

**Для проверки выполните**:
```
sudo ./nesca4 google.com
```

## ОШИБКА ЭКСПОРТА
Если вы получаете ошибку типа: (./nesca4: error while loading shared libraries), значит, одна из библиотек не хочет линковаться через rpath. 

**Чтобы это исправить вы можете выполнить:**
```
sudo make install-libs
```
**PS:** Это команда обязательно должна быть запущена через `sudo`, или хотя бы `su`, ведь устанавливает библиотеки в `/root` раздел.

**PS:** Также, чтобы исправить эту ошибку вы можете перекомпилировать _nesca4_, без библиотеки вызвавшей ошибку. Как это сделать уже было сказано в главе (_"ДРУГАЯ КОНФИГУРАЦИЯ"_).





















