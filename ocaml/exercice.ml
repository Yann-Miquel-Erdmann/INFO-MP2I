type fourniture =
  | Stylo of string (* couleur *)
  | Regle of int * bool (* taille en cm, centree ou non *)
  | Gomme

type trousse = fourniture list

let prix (fourn : fourniture) : float =
  match fourn with
  | Gomme -> 1.5
  | Stylo "bleu" -> 1.2
  | Stylo _ -> 1.0
  | Regle (longueur, _) -> 1.0 +. (float_of_int longueur /. 15.0)

let rec prix_trousse (t : trousse) : float =
  match t with [] -> 5. | f :: q -> prix f +. prix_trousse q

type 'a liste = 
    | Vide 
    | Cons of 'a * 'a liste
;;

let rec longueur (l: 'a liste): int = 
    match l with
    | Vide -> 0
    | Cons (_, q) -> longueur q + 1
;;

let rec affiche (l: 'a liste): unit = 
    match l with
    | Vide -> print_newline()
    | Cons(x,q) -> print_int x; print_string " "; affiche  q; 


    