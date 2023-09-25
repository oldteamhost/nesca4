AUTOMAKE_OPTIONS = foreign
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = nesca4

nesca4_SOURCES = nesca4.cc \
modules/hikvision.cc \
modules/negatives.cc \
files.cc \
html.cc \
nescalog.cc \
nescathread.cc \
other.cc \
portscan.cc \
scanner.cc \
services.cc \
bruteforce.cc \
target.cc \
ncbase/base64.c \
ncbase/binary.c \
ncbase/getopt.c \
ncbase/json.c \
ncsock/base.c \
ncsock/bruteforce.c \
ncsock/dns.c \
ncsock/ftp.c \
ncsock/http.c \
ncsock/icmp4.c \
ncsock/ip4.c \
ncsock/socket.c \
ncsock/socks5.c \
ncsock/strbase.c \
ncsock/tcp.c \
ncsock/rvi.c \
ncsock/smtp.c

nesca4_LDFLAGS = -Llib/platform/linux -pthread
nesca4_LDADD = -lhcnetsdk
nesca4_LDFLAGS += -Wl,-rpath,lib/platform/linux
