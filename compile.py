import os

print("Nesca4 compile on linux....")
print("[1] Debian [2] Arch")
what = input("Enter num: ")
what1 = input("Delete dependencies after compile? (y,n): ")

if (what == str(1)):
    print("\nCompile on debian...")
    os.system("sudo apt-get install libboost-all-dev")
    os.system("sudo apt-get install libcurl4-openssl-dev")
    os.system("sudo apt install g++ make git")
    os.system("make")
    if (what1 == "y"):
        os.system("sudo apt remove libboost-all-dev")
        os.system("sudo apt remove libcurl4-openssl-dev")
    print("\nsure.....")

if (what == str(2)):
    print("\nCompile on arch...")
    os.system("sudo pacman -S boost")
    os.system("sudo pacman -S curl git")
    os.system("make")
    if (what1 == "y"):
        os.system("sudo pacman -Rcs boost")
        os.system("sudo pacman -Rcs curl git")
    print("\nsure.....")
    
