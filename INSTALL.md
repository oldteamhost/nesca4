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

## CONFIGURE
Now comes the stage of customizing the source code, and setting up its compilation.

**First, you need to go to the directory with the code nesca4:**
```
cd nesca4
```
Note that the nesca4 directory must be in your current directory.

**Then you need to run the file (configure):**
```
./configure
```
### OPTIONS CONFIGURE
This is not a mandatory step, but if you need to customize the source code it is a must.

**To disable the hikvision library, run configure with this option:**
```
./configure --disable-hikvision
```
**To disable the dvr library, run configure with this option:**
```
./configure --disable-dvr
```
**You can also use them together:**
```
./configure --disable-dvr --disable-hikvision
```

## COMPILE
Now the compilation stage, after that you can already use nesca4.

**To compile, execute:**
```
make
```
**You can also speed it up by running it in threads:**
```
make -j
```
**PS:** First would be compiling the ncsock library, then already compiling nesca4 and linking it all together.

## START NESCA4
If the compilation was successful and no (error:) appears, you have an executable file nesca4 in your current folder, this is the program itself, it is ready to be used.

**To test launch, execute:**
```
sudo ./nesca4 google.com
```
### EXPORT ERROR
If you get an error like: (./nesca4: error while loading shared libraries), then one of the libraries does not want to be installed via rpath.
**In order to fix this you can perform:**
```
sudo make install-libs
```
**PS:** Running this command must necessarily be via (sudo) or at least (su).

Also, to fix this error, you can simply recompile nesca4 without the library that caused the error.
