type boisson = 
  | Eau 
  | Jus of string 
  | Breiz of bool
  | Cocktail of boisson *  boisson* float
  ;;


(* renvoie le prix d'une boisson b *)
let rec prix (b:boisson) : float = 
  match b with
  | Eau -> 0.
  | Jus jus -> if jus = "ramboutan" then 5.30 else 3.
  | Breiz _-> 1.
  | Cocktail (b1,b2,q) -> q*.(prix b1) +. (1.-.q)*.(prix b2)
;;
assert(prix (Eau)  = 0. );;
assert(prix (Jus "fraise")  = 3. );;
assert(prix (Jus "ramboutan")  = 5.3 );;
assert(prix (Breiz true)  = 1. );;
assert(prix (Cocktail(Eau, Cocktail(Breiz true, Jus "ramboutan",0.5), 0.5))  = 1.575 );;

(* crée une boisson à partir d'une liste de boissons l *) 
let rec shaker (l: boisson list): boisson = 
  match l with
  | b::[] -> b
  | b::q -> Cocktail (b, shaker (q),0.5)
  | [] -> failwith "impossible"
  ;;

(* renvoie le nom de la boisson sous la forme d'une chaîne de caractères *)
let string_of_boisson  (b:boisson): string = 
  match b with
  | Eau -> "Eau"
  | Jus x -> "Jus de "^x
  | Breiz x -> "Breiz Cola"
  | Cocktail (_,_,_) -> failwith "impossible"
;;
assert(string_of_boisson Eau = "Eau");;
assert(string_of_boisson (Jus "fraise") = "Jus de fraise");;
assert(string_of_boisson (Breiz false) = "Breiz Cola");;


(* renvoie la liste des ingrédients de la boisson b *)
let ingredients (b: boisson): (boisson*float) list =
  let rec ingredients_fraction (bois:boisson) (q:float): (boisson*float)list =
    match bois with
    | Cocktail (b1,b2,q1) -> List.concat [ingredients_fraction b1 (q1*.q) ; ingredients_fraction b2 ((1.-.q1)*.q)]
    | x -> [(x,q)]
  in ingredients_fraction b 1.;;


assert(ingredients (Cocktail(Eau, Cocktail(Breiz true, Jus "pomme",0.4), 0.5)) = [(Eau, 0.5); (Breiz true, 0.2); (Jus "pomme", 0.3)]);;
assert(ingredients (Cocktail(Eau, Eau, 0.3)) = [(Eau, 0.3); (Eau, 0.7)]);;

(* renvoie x à la puissance n (complexité O(n))*)
let rec puissance_n (x: float) (n:int): float = match n with
| 0 -> 1.
| _ -> x *. (puissance_n x (n-1)) 
;;
(* fait l'arrondi à n décimales (complexité O(n)) *)
let arrondi (x: float) (n: int): float = ((Float.round (x*.(puissance_n 10. n)))/.(puissance_n 10. n));;

(* regroupe les couple de l selon leur première composante et somme leur deuxième composante *)
let agreg_sum (l: (('a*float )list)): (('a*float) list) = 
  let rec agreg_sum_inner (l: (('a*float )list)) (count: float):(('a*float) list) =
    match l with
    | [] -> []
    | (x_nom, x_quant)::[] -> [(x_nom, arrondi (x_quant+.count) 2)]
    | (x_nom, x_quant)::(y_nom, y_quant)::q -> if x_nom = y_nom then agreg_sum_inner ((y_nom, y_quant)::q) (arrondi (x_quant+.count) 2) else (x_nom, arrondi (x_quant+.count) 2) ::(agreg_sum_inner ((y_nom, y_quant)::q) 0.)
  
  in agreg_sum_inner l 0.
;;
      

assert(agreg_sum [("bla",0.1);("bla",0.3);("truc",0.4);("truc",0.2)] = [("bla",0.4);("truc",0.6)]);;

(* affiche a recette de la boisson b *)
let recette (b:boisson): unit = 
  let rec recette_inner (l: (boisson*float) list): string = 
    match l with
    | [] -> "Recette pour un 1L:\n"
    | (x, quantite)::q -> (recette_inner q)^((string_of_int (int_of_float (quantite*.1000.))) ^ " mL " ^ (string_of_boisson x)  ^ "\n")
  in print_string (recette_inner (agreg_sum (ingredients b)))
;;
