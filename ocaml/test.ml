let rec longeur (l: 'a list) (n: int): int = 
  match l with
| [] -> n
| _::q -> (longeur q (n+1))
;;

let rec somme (l: int list) (s: int): int = 
  match l with
  | [] -> s
  | x::q->somme q (s+x)
;;


let rec renverse (l1: 'a list) (l2: 'a list): 'a list=
  match l1 with
  | [] -> l2
  | x::q -> renverse q (x::l2)
;;

let rec map (f: 'a->'b) (l1: 'a list) (l2: 'b list): 'b list = 
  match l1 with
  | [] -> renverse l2 []
  | x::q -> map f q ((f x)::l2)
;;

