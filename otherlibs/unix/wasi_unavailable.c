/* (C) 2021, Figly, Inc.
  Author: Gerd Stolpmann
  All rights reserved.  This file is distributed under the terms of
  the GNU Lesser General Public License version 2.1, with the
  special exception on linking described in the file LICENSE.
*/

#include <caml/mlvalues.h>
#include <caml/fail.h>

#define UNAVAILABLE1(cname, camlname)                    \
    CAMLprim value cname(value arg1) {                   \
      caml_invalid_argument(camlname " not available");   \
    }

#define UNAVAILABLE2(cname, camlname)                    \
    CAMLprim value cname(value arg1, value arg2) {       \
      caml_invalid_argument(camlname " not available");   \
    }

#define UNAVAILABLE3(cname, camlname)                    \
    CAMLprim value cname(value arg1, value arg2, value arg3) { \
      caml_invalid_argument(camlname " not vailable");   \
    }

#define UNAVAILABLE4(cname, camlname)                    \
    CAMLprim value cname(value arg1, value arg2, value arg3, value arg4) { \
      caml_invalid_argument(camlname " not available");   \
    }

#define UNAVAILABLE5(cname, camlname)                    \
    CAMLprim value cname(value arg1, value arg2, value arg3, value arg4, value arg5) { \
      caml_invalid_argument(camlname " not available");   \
    }

UNAVAILABLE1(unix_wait, "Unix.wait")
UNAVAILABLE2(unix_waitpid, "Unix.waitpid")
UNAVAILABLE2(unix_sigprocmask, "Unix.sigprocmask")
UNAVAILABLE1(unix_sigpending, "Unix.sigpending")
UNAVAILABLE1(unix_sigsuspend, "Unix.sigsuspend")
UNAVAILABLE2(unix_kill, "Unix.kill")
UNAVAILABLE1(unix_getpwnam, "Unix.getpwnam")
UNAVAILABLE1(unix_getpwuid, "Unix.getpwuid")
UNAVAILABLE1(unix_getgrnam, "Unix.getgrnam")
UNAVAILABLE1(unix_getgrgid, "Unix.getgrgid")
UNAVAILABLE1(unix_alarm, "Unix.alarm")
UNAVAILABLE2(unix_chmod, "Unix.chmod")
UNAVAILABLE3(unix_chown, "Unix.chown")
UNAVAILABLE1(unix_chroot, "Unix.chroot")
UNAVAILABLE2(unix_dup, "Unix.dup")
UNAVAILABLE3(unix_dup2, "Unix.dup2")
UNAVAILABLE2(unix_execv, "Unix.execv")
UNAVAILABLE3(unix_execve, "Unix.execve")
UNAVAILABLE2(unix_execvp, "Unix.execvp")
UNAVAILABLE3(unix_execvpe, "Unix.execvpe")
UNAVAILABLE1(unix_fork, "Unix.fork")
UNAVAILABLE1(unix_getegid, "Unix.getegid")
UNAVAILABLE1(unix_geteuid, "Unix.geteuid")
UNAVAILABLE1(unix_getgid, "Unix.getgid")
UNAVAILABLE1(unix_getlogin, "Unix.getlogin")
UNAVAILABLE1(unix_getuid, "Unix.getuid")
UNAVAILABLE1(unix_gethostname, "Unix.gethostname")
UNAVAILABLE1(unix_getpid, "Unix.getpid")
UNAVAILABLE1(unix_getppid, "Unix.getppid")
UNAVAILABLE2(unix_mkfifo, "Unix.mkfifo")
UNAVAILABLE2(unix_pipe, "Unix.pipe")
UNAVAILABLE1(unix_setgid, "Unix.setgid")
UNAVAILABLE1(unix_setsid, "Unix.setsid")
UNAVAILABLE1(unix_setuid, "Unix.setuid")
UNAVAILABLE5(unix_spawn, "Unix.spawn")
UNAVAILABLE1(unix_umask, "Unix.umask")
