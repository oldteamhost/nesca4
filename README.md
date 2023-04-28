# nesca4 в разработке....
## Половина функций ещё не рабочая!!
Консольная утилита для сканирования `портов` и `dns`, брутфорсер для `ftp`, `sftp`, `hikvision` и `rvi`.
Поддерживает многопоточность: До `500` потоков работает стабильно, дальше за ваш процессор не ручаюсь.
Использует `TCP` сканирования, но поддерживает полную настройку его. Разогнать можно очень сильно.
Полностью кроссплотформлена, для компиляции на `linux` используйте `gcc` для `windows` `MinGW`.

# UPDATE
+ Добавлена многопоточность для сканирования портов.
+ Добавлены оригинальные цвета с nesca3.
+ Настроен вывод.

# Документация
## Цель
Для указания цели есть эти аргументы:

- `-ip` - Указать в качестве цели обычный айпи, можно указать несколько, через запятую без пробела.

- `-cidr` - Указать в качесте цели `cidr`, можно указать несоклько, через запятую без пробела.

- `-import-ip` - Указать в качесте цели файл, с обычными айпи, каждый новый айпи на новой строчке.

- `-import-cidr` - Указать в качесте цели файл, с `cidr`, каждый новый `cidr` на новой строчке.

Для генерации рандомной цели есть эти:

- `-random-ip` - Указать в качстве цели рандомные айпи, в качестве параметра передавайте количество рандомный айпи.

## Порты
Для указания портов есть эти аргументы:

- `-ports, -p` - Указать порты на сканирование, можно указать несоклько через запятую: `80,20,22,443`.
Также можно вместо цифры указать - `all` для сканирования всех портов, или - `100` для указания 
топ 100 самых популярных портов, или - `50` для указания топ 50 самый популярных портов.


## Потоки
Для работы с потоками есть эти аргументы:

- `-threads, -T` - Позволяет указать количество потоков, они пердаються в параметр аргумента.
- `-timeout, -t` - Позволяет изменить задержку, для сканирования, стандартно `70`.

## DNS сканирования
Для работы с `dns` сканированием есть эти аргументы:

- `-dns-scan` - Включает сканирование `dns`, в параметр принимает, домен первого уровня: **.ru .net .com**
- `-dns-length` - Изменить длинну генерируемого домена, стандартно `5`. Длинну указывать в параметр.
- `-dns-dict` - Позволяет изменить словарь, из которого генерируеться рандомная строка, стандартный: `0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`.
Словарь указывать в качестве параметра.

## Сохранение
Для сохраниня результатов можно использывать эти аргументы:

- `-txt` - Позволяет сохранять результат в `txt`, причём если включен `debug` то он будет записывать и не удачные результаты.
- `-html` - Аналогично `txt`, только в `html`.

## Вывод
Для изменения вывода программы используйте эти аргументы:

- `-db` - Включает `debug` при котором будет выводить и сохраняться даже неудачные цели.
- `-clean` - Выключает вывод вообще, но сохранение до сих пор работает.
- `-log-set` - Позволяет изменить значение просканированных айпи после каторого, будет выводиться информация
о том сколько осталось. Стандартно `100`.

## Настройки сканирования
Для настройки сканирования есть эти аргументы:

- `-ping-off` - Отключить определение времени ответа хоста.
- `-dns-off` - Отключить получение dns у портов 443, 80.

## Настройки брутфорса
Для настройки брутфорса используйте эти аргументы:

- `-ftp-brute` - Включить брутфорс `ftp`.
- `-ftp-login` - Изменить путь к файлу в котором храняться логины для брутфорса ftp. Стандартно стоит `passwd/ftp_logins.txt`
- `-ftp-pass` - Изменить путь к файлу в котором храняться пароли для брутфорса ftp. Стандартно стоит `passwd/ftp_passwords.txt`
- `-ssh-brute` - Включить брутфорс `ssh`.
- `-ssh-login` - Аналогично `ftp-login`, стандартно: `passwd/ssh_logins.txt`
- `-ssh-pass` - Аналогично `ftp-pass`, стандартно: `passwd/ssh_passwords`




