
type 'a arbre =
  | V
  | N of 'a arbre  * 'a  * 'a arbre (* gauche, étiquette, droite *)

(* recherche x dans a et renvoie true si x est dans a *)
let rec recherche (x: 'a) (a: 'a arbre): bool =
  match a with
  | V -> false
  | N (g,y,d) -> if y = x then true else
      begin
        if y<x then recherche x d else recherche x g
      end

(* ajoute x et renvoie un ABR *)
let rec ajoute (x: 'a) (a:'a arbre): 'a arbre = 
  match a with
  | V -> N(V,x,V)
  | N (g,y,d) when x=y -> a
  | N (g,y,d) -> if y<x then N(g,y,ajoute x d) else N(ajoute x g,y,d)


let rec extraire_max (a: 'a arbre): 'a * 'a arbre =
  match a with
  | V -> failwith "il n'y a pas de max dans un arbre vide"
  | N (V,y,V) -> (y,V)
  | N (g,y,d) -> let m,a_max = extraire_max d in (m,N(g,y,a_max))






let rec supprime (x: 'a) (a:'a arbre): 'a arbre = 
  match a with
  | V  -> failwith "x n'est pas dans l'arbre" 
  | N(V,y,V) when y!=x -> failwith "x n'est pas dans l'arbre" 
  | N(g,y,d) when y=x -> let m, new_g = extraire_max g in N(new_g,m,d) 
  | N(g,y,d) -> if y<x then N(g,y,supprime x d) else N(supprime x g,y,d)



let time_a (n:int): float =
  let start  = Sys.time () in
   let rec time_a_inner (n_inner:int): int arbre = 
    match n_inner with
    | 0 -> V
    | _ -> ajoute n_inner (time_a_inner (n_inner-1))

  in let a = time_a_inner n in
  Sys.time () -. start
