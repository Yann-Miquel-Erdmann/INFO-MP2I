(* renvoie la somme des éléments de la liste l *)
let rec somme (l : int list) : int =
  match l with
  | [] -> 0
  | x :: q -> x + somme q
;;

assert (somme [ 1; 2; -3; 4 ] = 4);;
assert (somme [ 1; 2; 3; 4 ] = 10);;
assert (somme [ 0; 0; 0 ] = 0);;
assert (somme [] = 0)

(* renvoie true si x est dans la liste l *)
let rec recherche (l : 'a list) (v : 'a) : bool =
  match l with
  | [] -> false
  | x :: q -> x = v || recherche q v
;;

assert (recherche [ 1; 2; -3; 4 ] 0 = false);;
assert (recherche [ 1; 2; -3; 4 ] 1 = true);;
assert (recherche [ 1; 2; -3; 4 ] 4 = true);;
assert (recherche [ 1; 2; -3; 4 ] (-3) = true);;
assert (recherche [] 5 = false)

(* renvoie la concaténation des listes l1 et l2 *)
let rec concatener (l1 : 'a list) (l2 : 'a list) : 'a list =
  match l1 with
  | [] -> l2
  | x :: q -> x :: concatener q l2
;;

assert (concatener [] [] = []);;
assert (concatener [ 1; 2; 3 ] [] = [ 1; 2; 3 ]);;
assert (concatener [] [ 1; 2; 3 ] = [ 1; 2; 3 ]);;
assert (concatener [] [ 1; 2; 3 ] = [ 1; 2; 3 ]);;
assert (concatener [ 1; 2; 3 ] [ 4; 5; 6 ] = [ 1; 2; 3; 4; 5; 6 ])

(* concatène une liste de listes*)
let rec multi_concat (l : 'a list list) : 'a list =
  match l with
  | [] -> []
  | x :: [] -> x
  | x :: y :: q -> multi_concat (concatener x y :: q)
;;

assert (multi_concat [] = []);;
assert (multi_concat [ [] ] = []);;
assert (multi_concat [ []; [] ] = []);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ] ] = [ 1; 2; 3; 4 ]);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ]; [ 5; 6 ] ] = [ 1; 2; 3; 4; 5; 6 ]);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ]; []; [ 5; 6 ]; [] ] = [ 1; 2; 3; 4; 5; 6 ]);;

(* renvoie la concaténation de chaînes de caractères de l*)
let rec string_cat (l: string list) : string=
  match l with
  | [] -> ""
  | s::[] -> s
  | s1::s2::q -> string_cat ((s1^s2)::q)
;;

assert(string_cat [] = "");;
assert(string_cat ["test"] = "test");;
assert(string_cat ["test1"; "test2"] = "test1test2");;
assert(string_cat ["test1"; "test2"; "test3"] = "test1test2test3");;


let rec fold (f: 'a -> 'b ->'b) (l:'a list) (a:'b): 'b = 
  match l with
  | [] -> a
  | x::q -> f x (fold f q a)
;;

fold (fun x y->x^y) ["vive"; " "; "Ocaml"; "!!!"] "";; 
fold (^) ["vive"; " "; "Ocaml"; "!!!"] "" ;;
fold (+) [1;2;3;4] 0 ;;
fold (fun x l -> x::l) [1;2;3;4] [] ;;


let somme (l: int list): int = fold (+) l 0;;
assert (somme [ 1; 2; -3; 4 ] = 4);;
assert (somme [ 1; 2; 3; 4 ] = 10);;
assert (somme [ 0; 0; 0 ] = 0);;
assert (somme [] = 0);;

let recherche (l: 'a list) (v: 'a): bool = fold (fun x y-> x=v || y) l false;; 
assert (recherche [ 1; 2; -3; 4 ] 0 = false);;
assert (recherche [ 1; 2; -3; 4 ] 1 = true);;
assert (recherche [ 1; 2; -3; 4 ] 4 = true);;
assert (recherche [ 1; 2; -3; 4 ] (-3) = true);;
assert (recherche [] 5 = false)

let multi_concat (l : 'a list list) : 'a list = fold concatener l [];;
assert (multi_concat [] = []);;
assert (multi_concat [ [] ] = []);;
assert (multi_concat [ []; [] ] = []);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ] ] = [ 1; 2; 3; 4 ]);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ]; [ 5; 6 ] ] = [ 1; 2; 3; 4; 5; 6 ]);;
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ]; []; [ 5; 6 ]; [] ] = [ 1; 2; 3; 4; 5; 6 ]);;


let compose_liste (l:('a->'a) list): 'a->'a = fold (fun f g->fun x->f (g x)) l (fun x->x);;




let est_pair (x: int): bool = x mod 2 = 0;;

let rec filter (l: 'a list) (f: 'a ->bool): ('a list)=
  match l with 
  | []->[]
  | x::q -> if f x then x::(filter q f ) else (filter q f );;

assert(filter [] est_pair = []);;
assert(filter [1;2;3;4;5;6;8; 8; 2;10] est_pair = [2; 4; 6; 8; 8; 2; 10]);;

let rec filter (l: 'a list) (f: 'a ->bool): ('a list)= fold (fun x y->if f x then x::y else y) l [];;
assert(filter [] est_pair = []);;
assert(filter [1;2;3;4;5;6;8; 8; 2;10] est_pair = [2; 4; 6; 8; 8; 2; 10]);;

(* renvoie la liste de chaque élément de l appliqué à la fonction f *)
let rec map (f : 'a -> 'b) (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | x :: q -> f x :: map f q
;;
assert (map (fun x -> 2 * x) [] = []);;
assert (map (fun x -> 2 * x) [ 1; 2; 3 ] = [ 2; 4; 6 ]);;
assert (map (fun x -> 0) [ -1; -2; -3 ] = [ 0; 0; 0 ])


let rec map (f : 'a -> 'b) (l : 'a list) : 'a list = fold (fun x y->(f x)::y) l [];;
assert (map (fun x -> 2 * x) [] = []);;
assert (map (fun x -> 2 * x) [ 1; 2; 3 ] = [ 2; 4; 6 ]);;
assert (map (fun x -> 0) [ -1; -2; -3 ] = [ 0; 0; 0 ])


let list_of_string (s: string): char list = 
  let rec list_of_string_rec (s: string) (l: char list) (n:int): char list=
    match String.length s-n with
    | 0 ->l
    | i -> list_of_string_rec s (s.[i-1]::l) (n+1)

  in list_of_string_rec s [] 0;;




let string_of_list (l: char list): string = String.of_seq (List.to_seq l);;

let split (c:char) (s:string) : string list = 

    let rec split_from_i (s:string) (i:int) (curr:char list): string list = 
      match String.length s -i with
      | 0 -> [string_of_list curr]
      | x -> if s.[x-1]=c then( string_of_list curr )::split_from_i s (i+1) [] else split_from_i s (i+1) (s.[x-1]::curr)

    in List.rev (split_from_i s 0 []);;

