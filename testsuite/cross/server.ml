open Printf

module type TESTFUNCTOR = functor (Dummy : sig end) -> sig end
module type CROSSMODULE =
  sig
    val testname:string
    module Testmodule : TESTFUNCTOR
  end

let registry = ref []

module Register(C:CROSSMODULE) = struct
  let run() =
    Testing.init();
    ( try
        let module M = C.Testmodule(struct end) in
        raise Exit
      with
        | Exit ->
            Testing.exec_exit()
        | exn ->
            printf "Exception: %s\n" (Printexc.to_string exn)
    );
    flush stdout

  let () =
    registry := (C.testname, run) :: !registry
end

(* e.g. do Register(Cross12) *)


let port = 6543

let input_line fd =
  (* carefully read only until LF *)
  let line = Buffer.create 80 in
  let cont = ref true in
  let buf = Bytes.create 1 in
  while !cont do
    let n, ignore =
      try
        (Unix.read fd buf 0 1, false)
      with
        | Unix.Unix_error(Unix.EAGAIN, _, _)
        | Unix.Unix_error(Unix.EINTR, _, _) -> (0, true) in
    if n=0 && not ignore then failwith "EOF before command";
    if n > 0 then (
      let c = Bytes.get buf 0 in
      if c = '\n' then
        cont := false
      else
        Buffer.add_char line c;
    )
  done;
  Buffer.contents line

let run() =
  Pervasives.at_exit (fun () -> raise Exit);
  let tmpdir = Sys.getenv "TMPDIR" in
  Unix.chdir tmpdir;
  let sock = Unix.socket Unix.PF_INET6 Unix.SOCK_STREAM 0 in
  Unix.setsockopt sock Unix.SO_REUSEADDR true;
  Unix.bind sock (Unix.ADDR_INET(Unix.inet6_addr_any,port));
  Unix.listen sock 5;
  eprintf "Listening on port %d\n%!" port;
  let cont = ref true in
  while !cont do
    let stream,_ = Unix.accept sock in
    let line = input_line stream in
    if line = "END" then
      cont := false
    else (
      let f =
        try List.assoc line !registry
        with Not_found ->
          eprintf "Test not found: %s\n%!" line;
          (fun () -> ()) in
      let saved_stdout = Unix.dup Unix.stdout in
      Unix.dup2 stream Unix.stdout;
      f();
      Unix.dup2 saved_stdout Unix.stdout;
      Unix.close saved_stdout;
    );
    Unix.close stream
  done;
  Unix.close sock;
  eprintf "Stopped server\n%!"
