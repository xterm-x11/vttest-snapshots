/* $Id: vttest.h,v 1.12 1996/06/24 23:50:21 tom Exp $ */

#ifndef VTTEST_H
#define VTTEST_H 1

#define VERSION "1.7b 1985-04-19"
#include <patchlev.h>

/* Choose one of these */

/* #define XENIX        ** XENIX implies UNIX                           */
#define UNIX            /* UNIX                                         */
/* #define VMS          ** VMS not done yet -- send me your version!!!! */
/* #define SARG20       ** Sargasso C for TOPS-20                       */
/* #define SARG10       ** Sargasso C for TOPS-10                       */

#ifdef HAVE_CONFIG_H
#include <config.h>
#define UNIX
#else

#ifdef SARG10
#include "sargasso.h"
#endif

#ifdef SARG20
#include "sargasso.h"
#endif

#define RETSIGTYPE void

#endif

#define SIG_ARGS int sig	/* FIXME: configure-test */

#include <stdio.h>

#ifdef UNIX

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#if HAVE_STRING_H
#include <string.h>
#endif

#include <ctype.h>

#if HAVE_TERMIOS_H && HAVE_TCGETATTR
#  define USE_POSIX_TERMIOS 1
#else
#  if HAVE_TERMIO_H
#    define USE_TERMIO 1
#  else
#    if HAVE_SGTTY_H
#      define USE_SGTTY 1
#      define USE_FIONREAD 1
#    else
       please fix me
#    endif
#  endif
#endif

#include <signal.h>
#include <setjmp.h>

#if USE_POSIX_TERMIOS
#  include <termios.h>
#  define TTY struct termios
#else
#  if USE_TERMIO
#    include <termio.h>
/*#    define TCSANOW TCSETA */
/*#    define TCSADRAIN TCSETAW */
/*#    define TCSAFLUSH TCSETAF */
#    define TTY struct termio
#    define tcsetattr(fd, cmd, arg) ioctl(fd, cmd, arg)
#    define tcgetattr(fd, arg) ioctl(fd, TCGETA, arg)
#    define VDISABLE (unsigned char)(-1)
#  else
#    if USE_SGTTY
#      include <sgtty.h>
#      define TTY struct sgttyb 
#    endif
#  endif
#endif

#if HAVE_SYS_FILIO_H
#  include <sys/filio.h>	/* FIONREAD */
#endif

#if !defined(sun) || !defined(NL0)
#  if HAVE_IOCTL_H
#   include <ioctl.h>
#  else
#   if HAVE_SYS_IOCTL_H
#    include <sys/ioctl.h>
#   endif
#  endif
#endif

/*FIXME: really want 'extern' for errno*/
#include <errno.h>

extern jmp_buf intrenv;
extern int brkrd;
extern int reading;
extern int max_lines;
extern int max_cols;
extern int min_cols;

#if USE_FCNTL
#include <fcntl.h>
#endif
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

/* my SunOS 4.1.x doesn't have prototyped headers */
#if defined(__GNUC__) && defined(sun) && !defined(__SVR4)
extern int fclose(FILE *);
extern int fflush(FILE *);
extern int fprintf(FILE *, const char *fmt, ...);
extern int ioctl(int, unsigned long, void *);
extern int printf(const char *fmt, ...);
extern int scanf(const char *fmt, ...);
#endif

/* main.c */
RETSIGTYPE onbrk(SIG_ARGS);
RETSIGTYPE onterm(SIG_ARGS);
int main(int argc, char *argv[]);
int menu(char *table[]);
int scanto(char *str, int *pos, int toc);
void bug_a(void);
void bug_b(void);
void bug_c(void);
void bug_d(void);
void bug_e(void);
void bug_f(void);
void bug_l(void);
void bug_s(void);
void bug_w(void);
void bye(void);
void chrprint(char *s);
void do_scrolling(void);
void initterminal(int pn);
void tst_bugs(void);
void tst_characters(void);
void tst_doublesize(void);
void tst_insdel(void);
void tst_keyboard(void);
void tst_movements(void);
void tst_reports(void);
void tst_rst(void);
void tst_screen(void);
void tst_vt52(void);

#endif /* VTTEST_H */
