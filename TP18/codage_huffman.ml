type huffman = 
|Leaf of int*char
|Node of int*huffman*huffman


let freq (a: huffman) : int = 
  match a with
  |Leaf (f,_) |Node (f,_,_) -> f

let fusion (a1: huffman) (a2: huffman): huffman = Node (freq a1 + freq a2, a1,a2)

let count_freqs (s:string) : (char, int)Hashtbl.t = 
  let t_p = ref (Hashtbl.create(128)) in 
  for i = 0 to String.length s -1 do
    if Hashtbl.mem !t_p s.[i] then
      Hashtbl.replace !t_p s.[i] (Hashtbl.find !t_p s.[i])
    else
      Hashtbl.replace !t_p (s.[i]) 1
  done;
  !t_p

let huffman_leaves (t: (char,int) Hashtbl.t): huffman list = 
  Hashtbl.fold (fun cle count res -> (Leaf (count, cle))::res) t [] 


let rec merge_sort (h_l: huffman list): huffman list = 
  let rec partage (h_l: huffman list) (l1: huffman list) (l2: huffman list):(huffman  list) * (huffman list) = 
    match h_l with
    | a1::a2::q -> partage q (a1::l1) (a2::l2)
    | a1::q -> partage q (a1::l1) l2
    | []-> (l1,l2)

  in let rec merge (l1: huffman list) (l2: huffman list) (out: huffman list): huffman list =
    match (l1,l2) with
    | ([],[]) -> out
    | (l,[]) | ([],l) -> List.concat [out; l]
    | (a1::q1,a2::q2) when freq a1 <= freq a2 -> merge q1 (a2::q2) (a1::out)  
    | (a1::q1,a2::q2) when freq a1 > freq a2 ->  merge (a1::q1) q2 (a2::out)
    | _ -> failwith "impossible"
  in 
    let a1, a2 = partage h_l [] [] in
    if List.length a1 > 1 then
      begin
        let a3 = merge_sort a1 in   
        let a4 = merge_sort a2 in
        merge a3 a4 []
      end
    else
      merge a1 a2 []

let rec insert_huffman (a: huffman) (l: huffman list): huffman list = 
  match l with
  | [] -> [a]
  | a1::q when (freq a1) < freq a -> a1::(insert_huffman a q)
  | a1::q when (freq a1) >= freq a -> a::(insert_huffman a1 l)
  | _ -> failwith "impossible"

let rec fusion_huffman (l: huffman list): huffman = 
  match l with
  | [] -> failwith "liste vide"
  | a::[] -> a
  | a1::a2::q ->fusion_huffman (insert_huffman (Node(freq a1 + freq a1, a1,a2) ) q)

let huffman_tree (s: string) : huffman = fusion_huffman (merge_sort (huffman_leaves (count_freqs s)))



let construire_table  (a:huffman): (char, bool list)Hashtbl.t = 
  let t = Hashtbl.create(128) in 
  let rec construire_table_chemin (a:huffman) (chemin: bool list): unit = 
    match a with
    | Leaf (_,c) -> Hashtbl.replace t c  (List.rev chemin)
    | Node (_,a1,a2) -> construire_table_chemin a1 (false::chemin) ; construire_table_chemin a2 (true::chemin)

  in 
  construire_table_chemin a [];
  t

(* let compression_huffman (s: string): bool list* huffman =  *)
  
