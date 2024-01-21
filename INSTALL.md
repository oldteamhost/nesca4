# INSTALL NESCA 4
This is not really an installation, it is a compilation from source code, for those who have never done it before it can be very confusing, watch each step carefully and ideally understand why it is needed.
## DEPENDENCIES
First you need to install the necessary dependencies for successful compilation, these are gcc compilers, g++ make utility and git.

**For Arch linux execute:**
```
sudo pacman -S git make gcc
```

**For Debian linux execute:**
```
sudo apt install build-essential git
```
Actually git is needed here for cloning the repository (downloading nesca4 code), gcc, g++, make for compiling this code.  

**PS:** Only dependencies for only two linuxes (arch and debian) are listed here, this is done because all others are based on those two, and say if you have Kali or Ubuntu you have to run debian commands, if you have manjaro you have to run arch commands.

## DOWNLOAD
Now we need to download the nesca4 source code to compile it later.

**If you installed (git) in the previous step, you can do just that:**
```
git clone https://github.com/oldteamhost/nesca4
```

**But you can do without git by downloading a zip archive from github and unzipping it:**
```
- Open https://github.com/oldteamhost/nesca4
- Click (<> CODE)
- Then click (Download ZIP)
- Unzip this archive, e.g. with (unzip):
```
**PS:** This method is more difficult because it requires some knowledge of the terminal.

## COMPILE
cd nesca4
./configure
make

COMPILE NOT DVR & HIKVISION:
make clean
./configure --disable-dvr --disable-hikvision
make
