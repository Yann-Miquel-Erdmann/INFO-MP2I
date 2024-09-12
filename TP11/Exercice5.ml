(* renvoie true si la liste est triée, faux sinon *)
let rec est_trie (l:(int list)): bool = 
  match l with
  | [] -> true
  | x::[] -> true
  | x::y::q -> if x<=y then est_trie (y::q) else false
;;

assert(est_trie []);;
assert(est_trie [1]);;
assert(est_trie [1; 2; 3]);;
assert(est_trie [1; 1; 1]);;
assert(not (est_trie [5; 4; 10]));;


(* sépare les éléments de l en deux listes, les éléments inférieurs à x et les éléments supérieurs à x  *)
let partition (l: 'a list) (x: 'a) : ('a list )* ('a list) = 
  let rec partition (l: 'a list) (x: 'a) (inf: 'a list) (sup: 'a list) : ('a list )* ('a list) = 
    match l with
    | [] -> (inf,sup)
    | y::q -> if y<=x then partition q x (y::inf) sup else partition q x inf (y::sup)

  in partition l x [] []
;;

assert(partition [] 1 = ([], []));;
assert(partition [1] 1 = ([1], []));;
assert(partition [2] 1 = ([], [2]));;
assert(partition [1; 2; 0] 1 = ([0;1], [2]));;


(* renvoie la liste l triée grâce à l'algorithme du tri rapide  *)
let rec tri_rapide (l: 'a list): 'a list = 
  match  l with
  | [] | _::[] -> l
  | x::q -> let a,b = partition q x in List.concat [tri_rapide a;[x]; tri_rapide b]
;;


assert(est_trie(tri_rapide []));;
assert(est_trie(tri_rapide [1]));;
assert(est_trie(tri_rapide [1;2;3;3;3]));;
assert(est_trie(tri_rapide [5;4;3;2;1]));;

(* fusionne deux liste triées l1 et l2 en une seule liste triée *)
let rec fusion (l1: 'a  list) (l2: 'a  list): 'a list = 
  match (l1,l2) with
  | [],x | x, []-> x;
  | x1::q1, x2::q2 -> if x1 <= x2 then x1::fusion q1 l2 else x2::fusion l1 q2
;;

assert(fusion [] [] = []);;
assert(fusion [1] [] = [1]);;
assert(fusion [] [1] = [1]);;
assert(fusion [5] [1] = [1;5]);;
assert(fusion [5;7] [6;8] = [5;6;7;8]);;

(* renvoie la liste l triée grâce à l'algorithme du tri fusion  *)
let rec tri_fusion (l:'a list) : 'a list = 

  let rec separe (l:'a list) (b: bool) (l1:'a list) (l2:'a list): ('a list) * ('a list)= 
    match l with
    | [] -> (l1,l2)
    | x::q -> if b then separe q (not b) (x::l1) l2 else separe q (not b) l1 (x::l2)
  in   
  match l with
  | [] -> []
  | [_] -> l
  | _::q -> let a,b = separe l false [] [] in fusion (tri_fusion a) (tri_fusion b)

;;

assert(est_trie(tri_fusion []));;
assert(est_trie(tri_fusion [1]));;
assert(est_trie(tri_fusion [1;2;3;3;3]));;
assert(est_trie(tri_fusion [5;4;3;2;1]));;