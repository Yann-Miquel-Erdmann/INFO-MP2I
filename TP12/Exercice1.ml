type 'a ab = 
| V (* Vide *)
| N of 'a * 'a ab * 'a ab (* Noeud: elem gauche, droite*)

(* exemple *)

let t = N(3,N(5,V,N(8, V,V)),N(7,V,V))

(* taille a renvoie le nombre total de noeuds  *)
let rec taille (a:'a ab): int = 
  match a with
  | V -> 0
  | N(x,g,d) -> 1 + taille g + taille d


let test_taille () =
assert(taille V = 0);
assert(taille t = 4);
assert(taille (N(2,t,t)) = 9)


(* renvoie la hauteur d'un arbre binaire *)
let rec hauteur (a: 'a ab): int = 
  match a with
  | V -> -1
  | N(x,g,d) -> 1 + max (hauteur g) (hauteur d)


let test_hauteur () = 
  assert(hauteur V = -1);
  assert(hauteur (N(1,V,V)) = 0);
  assert(hauteur t = 2)


(* renvoie vrai si a est une feuille *)
let est_feuille (a:'a ab): bool =
  match a with
  | N(_,V,V) -> true
  | _ -> false

let test_est_feuille () = 
assert(est_feuille (N(5,V,V)) = true);
assert(est_feuille t = false);
assert(est_feuille V = false);
assert(est_feuille (N(5,V,N(3,V,V))) = false)


(* renvoie le nombre de feuilles dans l'arbre a *)
let rec feuilles (a:'a ab): int= 

  match a with  
  | V -> 0
  | N(x,g,d) -> if est_feuille a then 1 else feuilles g + feuilles d 


let test_feuilles () = 
assert(feuilles V = 0);
assert(feuilles (N(1,V,V)) = 1);
assert(feuilles t = 2)


(* renvoie l'étiquette du noeud correspondant au chemin donné *)
let rec etiquette (a: 'a ab) (chemin: bool list): 'a= 
  match (a,chemin) with
  | (N(x,_,_), []) -> x
  | (N(_,f,_), false::q) | (N(_,_,f), true::q) -> etiquette f q
  | (_,_) -> failwith "le chemin n'est pas valide"

let test_etiquette () = 
assert(etiquette (N(5,V,V)) [] = 5);
assert(etiquette t [true] = 7);
assert(etiquette t [false; true] = 8)


(* renvoie l'étiquette du noeud correspondant au chemin donné, None  si le chemin n'est pas valide*)
let rec etiquette_opt (a: 'a ab) (chemin: bool list): 'a option =
  match (a,chemin) with
  | (N(x,_,_), []) -> Some x
  | (N(_,f,_), false::q) | (N(_,_,f), true::q) -> etiquette_opt f q
  | (_,_) -> None


let test_etiquette_opt () = 
assert(etiquette_opt (N(5,V,V)) [] = Some 5);
assert(etiquette_opt t [true] =Some 7);
assert(etiquette_opt (N(0,V,V)) [false; true] = None);
assert(etiquette_opt V [] =  None)



(* affiche l'arbre d'entiers a avec un parcours préfixe *)
let rec print_prefixe (a:int ab): unit = 
  match a with
  | V -> ()
  | N(x,g,d) -> 
    print_int x; 
    print_prefixe g; 
    print_prefixe d;
    ()



(* renvoie la liste des éléments de a dans l'ordre préfixe *)
let rec liste_prefixe (a: 'a ab): 'a list = 
  match a with
  | V -> []
  | N(x,g,d) ->x::(liste_prefixe g)@(liste_prefixe d)

let test_liste_prefixe () = 
  assert(liste_prefixe V = []);
  assert(liste_prefixe (N(3,V,V)) = [3]);
  assert(liste_prefixe t = [3;5;8;7])

  (* renvoie la liste des éléments de a dans l'ordre infixe *)
let rec liste_infixe (a: 'a ab): 'a list = 
  match a with
  | V -> []
  | N(x,g,d) ->(liste_infixe g)@[x]@(liste_infixe d)

let test_liste_infixe () = 
  assert(liste_infixe V = []);
  assert(liste_infixe (N(3,V,V)) = [3]);
  assert(liste_infixe t = [5;8;3;7])

(* renvoie la liste des éléments de a dans l'ordre postfixe *)
let liste_postfixe (a:'a ab): 'a list=
  let rec liste_postfixe_inner (a:'a ab): 'a list = 
    match a with
    | V -> []
    | N(x,g,d) -> x::(liste_postfixe_inner d)@(liste_postfixe_inner g)
  in List.rev (liste_postfixe_inner a)

  let test_liste_postfixe () = 
    assert(liste_postfixe V = []);
    assert(liste_postfixe (N(1,V,V)) = [1]);
    assert(liste_postfixe t = [8;5;7;3])
  
(* let liste_prefixe_2 (a: 'a ab): 'a list = 
  let rec liste_prefixe_inner (aa: 'a ab) (lst: 'a list): 'a list
    match aa with
    | V -> list
    | N(x,g,d) -> x::liste_prefixe_inner g (liste_prefixe_inner d) *)

     
