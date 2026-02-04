#include <fcntl.h>
#include <linux/capability.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/prctl.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *tty_n = getenv("TTY_NUMBER");
  if (!tty_n) {
    return -1;
  }

#define TTY_FILE_MAX_SIZE sizeof("/dev/tty100")
  char tty_file[TTY_FILE_MAX_SIZE];
  snprintf(tty_file, TTY_FILE_MAX_SIZE, "/dev/tty%s", tty_n);

  int tty = open(tty_file, O_RDONLY);
  int res = ioctl(tty, TIOCSCTTY, 1);
  if (res < 0) {
    perror("tiocnotty");
    return -1;
  }

  if (prctl(PR_CAPBSET_DROP, CAP_SYS_ADMIN, 0, 0, 0) < 0) {
    perror("prctl_capbset_drop");
    return -1;
  }

  ++argv;
  execvp(*argv, argv);
  return 0;
}
//  vim: set ts=2 sw=2 tw=0 et :
