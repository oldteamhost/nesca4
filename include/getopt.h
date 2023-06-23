#ifndef MY_GETOPT_H_INCLUDED
#define MY_GETOPT_H_INCLUDED

extern int getopt_reset(void);
extern int optind, opterr, optopt;
extern char *optarg;

struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

#undef no_argument
#define no_argument 0
#undef required_argument
#define required_argument 1
#undef optional_argument
#define optional_argument 2

extern int getopt_long(int argc, char * argv[], const char *shortopts,
                       const struct option *longopts, int *longind);

extern int getopt_long_only(int argc, char * argv[], const char *shortopts,
                            const struct option *longopts, int *longind);

extern int _getopt_internal(int argc, char * argv[], const char *shortopts,
                            const struct option *longopts, int *longind,
                            int long_only);

#endif
