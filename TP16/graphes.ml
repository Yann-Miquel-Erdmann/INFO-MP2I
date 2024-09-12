type graphe = int list array


let g0 = 
  [|
    [1]; (* voisins de 0 *)  
    [2;3];  (* voisins de 1 *)
    [0;3];  (* voisins de 2 *)
    [] (* voisins de 3 *)
  |]



let nb_aretes (g:graphe): int = 
  let l = Array.length g in
  let count_p = ref 0 in
  for i = 0 to l -1 do
    count_p:= !count_p+List.length g.(i)
  done;
  !count_p


let nb_aretes_no (g: graphe): int = (nb_aretes g) / 2

(* renvoie k**n *)
let exp_rapide (k:int) (n:int): int = 
  let n_p = ref n in
  let k_p = ref k in
  let res = ref 1 in
  while !n_p > 0 do
    if !n_p mod 2 = 1 then
      
      res := !res * !k_p;
      
    k_p := !k_p * !k_p;
    n_p := !n_p / 2
    

  done;
  !res


type 'a pile = 'a list ref
let pile_vide () = ref []

let empiler (p: 'a pile) (x: 'a): unit = p := x::!p

let depiler (p: 'a pile): 'a = 
  match !p with
  | [] -> failwith "impossible de dépiler"
  | x::q -> p:= q; x 

let rec noter_composante_source (g: graphe) (s: int) (k: int) (c:int array): unit = 
  let p = pile_vide () in
  empiler p s;
  c.(s) <- k;
  while !p <> [] do
    let u = depiler p in 
    let rec traiter_voisins (l: int list): unit = 
      match l with
      | [] -> ()
      | v::q -> begin
          if c.(v) = -1 then begin
            empiler p v;
            c.(v) <- k
            end; traiter_voisins q
      end  
    in traiter_voisins g.(u)
  done


let composantes_connexes (g: graphe): int array = 
  let n = Array.length g in
  let c = Array.make n (-1) in 
  let k = ref 1 in 
  for s = 0 to n-1 do
    if c.(s) = -1 then
      begin
        print_int s; print_endline "";
        noter_composante_source g s !k c;
        k := !k + 1 
      end
  done;
  c


let g = [|
  [1;2];
  [0;2];
  [1;0];
  [4;6];
  [3;5;6];
  [4;6];
  [3;5;6];
  [8;11];
  [7;9];
  [8;10];
  [9;11];
  [10;7];
|]