let () =
  at_exit Testing.finish ;;

let f = Format.sprintf "[%i]";;
print_endline (f 1);;
print_endline (f 2);;

let f = Format.asprintf "[%i]";;
print_endline (f 1);;
print_endline (f 2);;
