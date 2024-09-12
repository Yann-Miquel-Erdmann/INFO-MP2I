type expr =
| Const of float (* constante *)
| Add of expr * expr (* Add(e1, e2) correspond `ae1 + e2 *)
| Mul of expr* expr
| Var of string
| IFTE of boolexpr * expr * expr (* if b then e1 else e2 *)


and boolexpr = 
| BConst of bool (* constantes true et false *)
| Or of boolexpr * boolexpr (* OU booléen*)
| And of boolexpr * boolexpr (* ET booléen*)
| Not of boolexpr (* NON booléen*)
| Eq of expr * expr (* égalité *)
| Leq of expr * expr (* inférieur ou égal *)

type context = (string*float) list;;
(*** Exemples: ***)
(* représentation de 3.2 + 4 *)
let e1 = Add(Const 3.2, Const 4.)

(* représentation de (1 + 2) + (3 + (4 + 5)) *)
let e2 =Add(Add(Const 1.,Const 2.),Add(Const 3.,Add(Const 4.,Const 5.)))


(* x->2.0, r->-0.2 *)
let c1 = [("x", 2.0); ("r", -0.2)];;

(* renvoie la valeur associé a s dans le contexte c *)
let rec get_var (s: string) (c: context): float = 
  match c with
  | [] -> failwith ("la variable "^s^" n'est pas dans le contexte\n" )
  | (nom, valeur)::q -> if nom = s then valeur else get_var s q
;;

assert(get_var "x" c1 = 2.0);;
assert(get_var "r" c1 = -0.2);;



let rec var_count (e: expr) (v: string) : int = 
  match e with
  | Const _ -> 0
  | Var x -> if x = v then 1 else 0
  | Add (e1,e2) | Mul (e1,e2) -> var_count e1 v + var_count e2 v
  | IFTE (b,e1,e2) -> var_count_bool b v + var_count e1 v + var_count e2 v

  and var_count_bool (b: boolexpr) (v: string) : int = 
    match b with
    | BConst _ ->0
    | Not bb -> var_count_bool bb v 
    | Or (b1,b2)| And (b1,b2) -> var_count_bool b1 v + var_count_bool b2 v
    | Eq (e1,e2)| Leq (e1,e2) -> var_count e1 v + var_count e2 v
  ;;


(* calcule le résultat de expression e dans le contexte c *)
let rec eval (e: expr) (c: context): float = 
  match e with
  | Const x -> x
  | Var s -> get_var s c
  | Add (x,y) -> eval x c +. eval y c
  | Mul (x,y) -> eval x c *. eval y c
  | IFTE (b,x,y) -> if eval_bool b c then eval x c else eval y c

(* calcule le résultat de expression booléenne b dans le contexte c *)
and eval_bool (b: boolexpr) (c: context): bool= 
  match b with
    | BConst bb -> bb
    | Not bb -> not (eval_bool bb c)
    | Or (b1,b2) -> eval_bool b1 c || eval_bool b2 c
    | And (b1,b2) -> eval_bool b1 c && eval_bool b2 c
    | Eq (e1,e2) -> if eval e1 c = eval e2 c then true else false
    | Leq (e1,e2) -> if (eval e1 c) <= (eval e2 c) then true else false
;;


assert(eval (Add(Add(Const 1.,Const 2.),Add(Const 3.,Add(Const 4.,Const 5.)))) []  = 15.);;
assert(eval (Add(Const 3.2, Const 4.)) [] = 7.2);;
assert(eval (Mul(Const 5., Add(Const 3.5,Const 0.5))) [] = 20.);;
assert(eval (Mul(Const 5., Add(Const 4.2,Var "r"))) c1 = 20.);;
assert(eval (IFTE (BConst true , Const 5. , Const 3.)) []  = 5.);;
assert(eval (IFTE (BConst false , Const 5. , Const 3.)) []  = 3.);;


assert(eval_bool (BConst true) []);;
assert(eval_bool (Not (BConst false)) []);;
assert(eval_bool (And (BConst true , BConst true)) []);;
assert(eval_bool (Not(And (BConst false , BConst true))) []);;
assert(eval_bool (Not(Or (BConst false , BConst false))) []);;
assert(eval_bool (Or (BConst true , BConst true)) []);;
assert(eval_bool (Eq (Const 5. , Const 5.)) []);;
assert(eval_bool (Not(Eq (Const 5. , Const (-2.)))) []);;
assert(eval_bool (Not(Leq (Const 5. , Const (-2.)))) []);;
assert(eval_bool (Leq (Const (-2.), Const 5. )) []);;



