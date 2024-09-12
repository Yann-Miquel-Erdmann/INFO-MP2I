type couleur = Rouge | Noir

type 'a noeud_arn = | F of 'a | N of couleur * 'a * 'a noeud_arn * 'a noeud_arn

type 'a arn = 'a noeud_arn option


let feuilles (a:'a arn): int = 
  let rec feuilles_noeud (aa: 'a noeud_arn): int = 
    match aa with
    | F _ -> 1
    | N (c,x,g,d) -> 1
  in match a with
  | None -> 0
  | Some r -> feuilles_noeud r


let couleur_noeud (a: 'a noeud_arn): couleur = 
  match a with
  | F _-> Noir
  | N (c,_,_,_)-> c

exception Erreur_hauteur_noire

let rec rouges_successifs (a:'a noeud_arn): bool = 
  match a with
  | F _ | N(_,_,F _, F _)-> false
  | N (Rouge,_,N (Rouge, _,_,_),_) | N (Rouge,_,_,N(Rouge , _ ,_ ,_ ))-> true
  | N (_, x, g,d) -> rouges_successifs g || rouges_successifs d 

let rec hauteur_noire (a:'a noeud_arn): int=
  match a with
  | F _ -> 0
  | N (Noir,_,g,d) -> let hg = hauteur_noire g in if hg = hauteur_noire d then (1+hg) else raise Erreur_hauteur_noire
  | N (Rouge,_,g,d) -> let hg = hauteur_noire g in if hg = (hauteur_noire d) then hg else raise Erreur_hauteur_noire 


let arn_valide (a:'a arn): bool= 
    match a with
    | None -> true
    | Some aa -> 
      if not (couleur_noeud aa = Noir) ||  rouges_successifs aa 
        then false
        else
          try hauteur_noire aa > 0 with
          | _ ->  false



let test_arn_valide (unit) = 
  assert(arn_valide None);
  assert(arn_valide (Some (N (Noir, 1, F 1, F 2) )));
  assert(not (arn_valide (Some (N (Rouge, 1, F 1, F 2) ))));
  assert(not (arn_valide (Some (N (Noir, 3 , N (Rouge, 2, N (Rouge, 1,F 1, F 2), F 2), F 2) ))));
  assert(arn_valide (Some (N (Noir, 3 , N (Rouge, 2, N (Noir, 1,F 1, F 2), N(Noir, 3, F 3, F 4)), N (Noir, 1,F 1, F 2)) )))




let correction_arn (abr: 'a noeud_arn):'a noeud_arn = 
  match abr with
  | N(Noir, z, N(Rouge, y,N(Rouge,x,a,b),c) ,d  ) 
  | N(Noir, z, N(Rouge, x,a,N(Rouge,y,b,c)) ,d  ) 
  | N(Noir, x, a, N(Rouge, z, N(Rouge,y,b,c),d))
  | N(Noir, x, a, N(Rouge, y, b, N(Rouge,z,c,d)))
    -> N(Rouge,y,N(Noir,x,a,b), N(Noir,z,c, d ))
  | _ -> abr


let rec insertARNrelax (x:'a) (a: 'a noeud_arn): 'a noeud_arn = 
  match a with
  | F y -> if x > y then N(Rouge, y, F y, F x) else N(Rouge, x, F x, F y)
  | N(c,y,g,d) -> if x > y then correction_arn (N(c,y,g,insertARNrelax x d)) else  correction_arn (N(c,y,insertARNrelax x g, d))

let insertionARN (x:'a) (a: 'a arn): 'a arn  = 

    match a with
    | None -> Some (F x)
    | Some aa   -> begin match insertARNrelax x aa with
                | N(_, y, g, d) ->Some(N (Noir, y,g,d)) 
                | F _ -> failwith "impossible"
                end

let testinsertionARN (unit) =
assert(insertionARN 1 None = Some (F 1));
assert(insertionARN 1 (Some (F 2)) = Some(N(Noir,1 ,F 1, F 2)));
assert(insertionARN 3 (Some (F 2)) = Some(N(Noir,2 ,F 2, F 3)));
assert(arn_valide (insertionARN 1 (Some (N(Noir, 2, N(Rouge, 0, F 0, F 2), F 3)))))


let rec b (n: int): 'a arn  = 
  match n with
  | 0 -> Some (F 0)
  | nn when nn>0 -> insertionARN nn (b (nn-1))
  | _ -> None 

let rec testB (n: int) = 
  assert(arn_valide (b n));
  match b n with
  | Some bb ->  assert(hauteur_noire bb <=. 2. *. (log (2. *. (float n) +. 1.) /. log 2.) )
  | _ -> assert(1)