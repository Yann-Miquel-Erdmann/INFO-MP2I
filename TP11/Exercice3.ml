let rec fold (f: 'a -> 'b ->'b) (l:'a list) (a:'b): 'b = 
  match l with
  | [] -> a
  | x::q -> f x(fold f q a)
;;

type couleur = Coeur | Carreau | Pique  | Trefle ;;

let couleur1 = Pique ;;


let est_rouge c = match c with
	| Coeur   -> true
	| Carreau -> true
	| Pique   -> false
	| Trefle  -> false ;;

assert (est_rouge Carreau);; (* vaut true *)

type carte = 
	| Nombre of (int * couleur) (* Cartes 2 à 10 *)
	| Valet of couleur
	| Dame of couleur
	| Roi of couleur
	| As of couleur

let carte_1 = Valet Coeur
let carte_2 = Nombre (9, Pique)

(* Renvoie la couleur d'une carte *)
let couleur_de_carte ca = match ca with
	| Nombre (_, c)  | Valet c 
	| Dame c | Roi c | As c -> c 
;;

assert (couleur_de_carte (Roi Trefle) = Trefle) ;;

let string_of_couleur (c: couleur): string = match c with
| Coeur -> "Coeur"
| Carreau -> "Carreau"
| Trefle -> "Trèfle"
| Pique -> "Pique"
;;


  

let string_of_carte (c: carte): string = 
  match c with
  | Nombre (n, couleur) -> (string_of_int n)^" de "^string_of_couleur couleur
  | Valet couleur -> "Valet"^" de "^(string_of_couleur couleur) 
  | Dame couleur -> "Dame"^" de "^(string_of_couleur couleur) 
  | Roi couleur -> "Roi"^" de "^(string_of_couleur couleur) 
  | As couleur -> "As"^" de "^(string_of_couleur couleur) 
;;

(* renvoie la valeur de la carte c, l'as a une valeur de 14, le roi 13, la Dame 12 et le valet 11 *)

let valeur_of_carte (c:carte): int = 
  match c with
  | Nombre (n, _)  -> n
  | Valet _ -> 11
  | Dame _ -> 12
  | Roi _ -> 13
  | As _ -> 14
;;

(* renvoie la carte de valeur v et de couleur c, l'as a une valeur de 14, le roi 13, la Dame 12 et le valet 11 *)
let carte_of_valeur (v:int) (c:couleur): carte = 
  match v with
  | 11 ->   Valet c
  | 12 ->   Dame c
  | 13 ->   Roi c
  | 14 ->   As c
  |  x ->   Nombre (x, c)
;;



(* renvoie une couleur aléatoire *)
let random_couleur (): couleur = 
  match Random.int 4 with
  | 0 -> Coeur
  | 1 -> Carreau
  | 2 -> Pique
  | _ -> Trefle  (*3, _ pour le pattern-matching *)


(* renvoie une carte aléatoire *)
let random_carte (): carte = carte_of_valeur (2+Random.int 13) (random_couleur ()) ;;

(* compare deux cartes, renvoie -1 si c1<c2, 0 c1==c2, 1 c1>c2*)
let cmp (c1: carte) (c2: carte):int = 
  if (couleur_de_carte c1) != (couleur_de_carte c2) then 
    if couleur_de_carte c1 < couleur_de_carte c2 then
      -1
    else
      1 
  else 
    if valeur_of_carte c1 = valeur_of_carte c2 then
      0
    else
      if valeur_of_carte c1 < valeur_of_carte c2 then
        -1
      else
        1
      ;;

assert (cmp carte_1 carte_1 = 0 );;
assert (cmp (Roi Coeur) (Valet Carreau) = -1 );;
assert (cmp (Valet Carreau) (Valet Pique) = -1 );;
assert (cmp (Valet Pique) (Valet Trefle) = -1 );;
assert (cmp (Valet Coeur) (Dame Coeur) = -1 );;
assert (cmp (Dame Coeur) (Roi Coeur) = -1 );;
assert (cmp (Nombre (3, Coeur)) (Nombre(2, Coeur)) = 1 );;

(* insère une carte c dans une liste de cartes l triées au bon endroit *)
let rec insert (c: carte) (l: carte list): carte list = 
  match l with
  | [] -> [c]
  | c1::q -> if c<=c1 then c::c1::q else c1::(insert c q)
;;
assert(insert (Valet Coeur) [] = [Valet Coeur]);;
assert(insert (Valet Coeur) [Valet Coeur] = [Valet Coeur; Valet Coeur]);;
assert(insert (Valet Carreau ) [Valet Coeur] = [Valet Coeur; Valet Carreau]);;
assert(insert (Dame Trefle ) [Valet Coeur; Roi Carreau] = [Valet Coeur; Dame Trefle;Roi Carreau; ]);;
assert(insert (Nombre (2, Pique) ) [Nombre (2, Pique); Nombre (10, Pique)] =  [Nombre (2, Pique);Nombre (2, Pique) ; Nombre (10, Pique)]);;
assert(insert (Nombre (5, Pique) ) [Nombre (2, Pique);Nombre (2, Pique); Nombre (10, Pique)] =  [Nombre (2, Pique);Nombre (2, Pique); Nombre (5, Pique) ; Nombre (10, Pique)]);;

(* trie une liste de cartes l avec l’algorithme du tri par insertion *)
let insert_sort (l: carte list): carte list = fold insert l [];;
assert(insert_sort [] = [] );;
assert(insert_sort [Valet Coeur] = [Valet Coeur] );;
assert(insert_sort [Dame Coeur; Valet Coeur; ] = [Valet Coeur; Dame Coeur] );;
assert(insert_sort [Dame Pique; Valet Coeur; ] = [Valet Coeur; Dame Pique] );;

let gen_couleur (c: couleur): carte list = 

  let rec inner (v: int): carte list= 
    match v with 
    | 14 -> [carte_of_valeur v c]
    | x -> (carte_of_valeur x c) :: inner (v+1)
in inner 2;;

assert(gen_couleur Pique = [Nombre (2, Pique); Nombre (3, Pique); Nombre (4, Pique); Nombre (5, Pique);
 Nombre (6, Pique); Nombre (7, Pique); Nombre (8, Pique); Nombre (9, Pique);
 Nombre (10, Pique); Valet Pique; Dame Pique; Roi Pique; As Pique]);;