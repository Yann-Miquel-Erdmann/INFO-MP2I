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
assert (multi_concat [ [ 1; 2 ]; [ 3; 4 ]; []; [ 5; 6 ]; [] ] = [ 1; 2; 3; 4; 5; 6 ])

(* renvoie la liste de chaque élément de l appliqué à la fonction f *)
let rec map (f : 'a -> 'b) (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | x :: q -> f x :: map f q
;;

assert (map (fun x -> 2 * x) [] = []);;
assert (map (fun x -> 2 * x) [ 1; 2; 3 ] = [ 2; 4; 6 ]);;
assert (map (fun x -> 0) [ -1; -2; -3 ] = [ 0; 0; 0 ])

(* concatène l1 et l2 en renversant l1 *)
let rec rev_concat (l1 : 'a list) (l2 : 'a list) : 'a list =
  match l1 with
  | [] -> l2
  | x :: q -> rev_concat q (x :: l2)
;;

assert (rev_concat [] [] = []);;
assert (rev_concat [] [ 1; 2; 3 ] = [ 1; 2; 3 ]);;
assert (rev_concat [ 1; 2; 3 ] [ 4; 5; 6 ] = [ 3; 2; 1; 4; 5; 6 ]);;
assert (rev_concat [ 1; 2; 3 ] [] = [ 3; 2; 1 ])

(* renverse la liste l *)
let reverse l = rev_concat l [];;

assert (reverse [] = []);;
assert (reverse [ 1; 2; 3 ] = [ 3; 2; 1 ]);;
assert (reverse [ 1 ] = [ 1 ])

(* renvoie les entiers de 0 à n-1 dans l'ordre décroissant *)
let rec dec_range (n : int) : int list =
  if n < 0
  then failwith "n must be positive"
  else (
    match n with
    | 0 -> []
    | _ -> (n - 1) :: dec_range (n - 1))
;;

(* renvoie les entiers de 0 à n-1 dans l'ordre croissant *)
let range (n : int) : int list = reverse (dec_range n);;

assert (range 0 = []);;
assert (range 1 = [ 0 ]);;
assert (range 5 = [ 0; 1; 2; 3; 4 ])

(* renvoie la liste des entiers de 0 à n-1 appliqués à la fonction f *)
let make_list (f : int -> 'a) (n : int) : 'a list = map f (range n);;

assert (make_list (fun x -> x * x) 5 = [ 0; 1; 4; 9; 16 ]);;
assert (make_list (fun x -> x * x) 1 = [ 0 ]);;
assert (make_list (fun x -> x * x) 0 = [])

let pair (x : int) : string = if x mod 2 = 0 then "pair" else "impair"
let repeter (s : string) : string = s ^ s
let rec compose_liste (l: ('a->'a) list ): 'a->'a =  
  match l with
  | [] -> fun x->x
  | f :: q -> fun x->f ((compose_liste q) x)
;;



