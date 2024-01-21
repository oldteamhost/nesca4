# Install nesca4

### DEPENDENCIES:
First, you need to install the necessary dependencies:

For arch linux execute:
```
  sudo pacman -S git make
```
     
For debian linux, run:
```
  sudo apt install build-essential git
```

DOWNLOAD:
Then you need to download the code nesca4:

If you already installed (git) in the previous step, do so:
  git clone https://github.com/oldteamhost/nesca4
  
You can do without git by simply downloading a zip archive from github and unzipping it:
  1. Click (<> CODE)
  2. Then click (Download ZIP)
  3. Unzip this archive, e.g. with (unzip)

cd nesca4
./configure
make

COMPILE NOT DVR & HIKVISION:
make clean
./configure --disable-dvr --disable-hikvision
make
