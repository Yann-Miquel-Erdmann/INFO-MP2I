type circuit = 
  | R of float
  | L of float
  | C of float
  | Par of circuit * circuit
  | Seq of circuit * circuit
;;

type complex = (float*float);;

Seq ((R 1.) , ( Par ((Seq ((R 3.),(L 3.))) , (C (1./.3.)))));;

(* compte le nombre de résistance dans le circuit c*)
let rec nb_R  (c: circuit) : int = 
  match c with
  | R _ -> 1
  | C _ | L _-> 0
  | Par (x ,y) | Seq (x ,y) -> (nb_R x) + (nb_R y) 
;;

(* ajoute les complexes a1+i b1, a2+ib2 *)
let add ((a1,b1): complex) ((a2,b2): complex): complex = (a1+.a2, b1+.b2);;

(* multiplie les complexes a1+i b1, a2+ib2 *)
let mul ((a1,b1): complex) ((a2,b2): complex): complex = (a1*.a2 -. b1*.b2 , a1*.b2 +. a2*.b2);;

(* renvoie le conjugué du complexe a1 + ib1 *)
let conj ((a1,b1): complex): complex = (a1, -.b1);;

(* renvoie l'inverse d'un complexe a1 + ib1 *)
let inv ((a1,b1): complex): complex = (a1 /. (a1*.a1 +. b1 *. b1) , -.b1 /. (a1*.a1 +. b1 *. b1));;


let rec impedance (c: circuit) (w: float): complex = 
  match c with
  | R r -> (r,0.)  
  | C c -> inv (0., w*.c) 
  | L l -> (0., w*.l)  
  | Seq (c1,c2) -> add (impedance c1 w) (impedance c2 w)
  | Par (c1,c2) -> inv (add (inv (impedance c1 w)) (inv (impedance c2 w)))
;;



let rec est_econome (c: circuit): bool = 
  match c with
  | R _ | C _ | L _  -> true
  | Par (R _ , R _ ) | Seq (R _ , R _ ) -> false
  | Par (c1,c2 )| Seq (c1,c2) -> est_econome c1 && est_econome c2 ;; 

assert(est_econome (Seq ((R 1.) , ( Par ((Seq ((R 3.),(L 3.))) , (C (1./.3.)))))) = true);;
assert(est_econome (Seq ((R 1.) , ( Par ((Seq ((R 3.),(R 3.))) , (C (1./.3.)))))) = false);;


let rec transforme_circuit (c: circuit): circuit =
  match c with
  | R _  | C _  | L _ -> c
  | Seq (R r1, R r2) -> R (r1+.r2) 
  | Par (R r1, R r2)-> R ((r1+.r2)/.(r1*.r2))
  | Par (c1,c2) r-> Par (transforme_circuit c1, transforme_circuit c2)
  | Seq (c1,c2) -> Seq (transforme_circuit c1, transforme_circuit c2)
;;
assert(transforme_circuit (Seq (R 1., R 2.)) = R 3.);;
assert(transforme_circuit (Par (R 1., R 2.)) = R 1.5);;
assert(transforme_circuit (Par (R 1., R 2.)) = R 1.5);;

