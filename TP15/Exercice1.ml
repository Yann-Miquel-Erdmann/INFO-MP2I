let array_range (n: int): int array = 
  let t = Array.make n 0 in
  for i = 0 to (n-1) do 
    t.(i) <- i
  done; 
  t

let somme (t: int array): int = 
  let res  = [|0|] in 
  let n = Array.length t in 
  for i = 0 to n-1 do 
    res.(0) <-  res.(0) + t.(i)
  done;
  res.(0)


let somme_2 (t: int array): int = 
  let res  = 0 in
  let res_p = ref res in 
  let n = Array.length t in 
  for i = 0 to n-1 do 
    res_p :=  !res_p + t.(i)
  done;
  !res_p

let argmax (t: 'a array) (end_indice: int): int = 
  let n = Array.length t in
  if  end_indice < 1 || n == 0 then -1 else
  let indice = 0 in 
  let indice_p = ref indice in
  for i = 0 to min (end_indice-1) n-1 do
    if t.(i) > t.(!indice_p) then
      indice_p := i
    else ()
  done;
  !indice_p

let print_array (t: int array): unit = 
  let n = Array.length t in 
  for i  = 0 to n-1 do
    print_int t.(i); print_string " ";
  done;
  print_endline ""

let tri (t: int array): int array = 
  let n = Array.length t in
  for i = 0 to n-2 do
    let max_i = argmax t (n-i+1) in
    let temp = t.(max_i) in
    t.(max_i) <- t.(n-i-1) ;
    t.(n-i-1) <- temp;

  done;
  t


let glouton_prix (c: int array) (n: int): int list=
  let c_l = Array.length c in
  let lst = [] in 
  let lst_p = ref lst in
  let n_p = ref n in
  for i = 0 to !n_p -1 do
    let indice = argmax c (min (c_l+1) (!n_p +2)) in
    if indice != 0 
    then 
      begin
        lst_p := (indice) :: !lst_p;
        n_p := !n_p - indice ;
        print_int !n_p
      end
  done;
  !lst_p

let glouton_ratio (c: int array) (n: int): int list = 
  let c_l = Array.length c in
  let ratios = Array.make c_l 0.0 in
  for i = 1 to c_l -1 do
    ratios.(i) <- (float_of_int c.(i))  /. (float_of_int i)
  done;
  print_array c;
  
  let lst = [] in 
  let lst_p = ref lst in
  let n_p = ref n in
  for i = 0 to !n_p -1 do
    let indice = argmax ratios (min (c_l+1) (!n_p +2)) in
    if indice != 0 
    then 
      begin
        lst_p := (indice) :: !lst_p;
        n_p := !n_p - indice ;
        print_int !n_p
      end
  done;
  !lst_p


let decoupe_prog_dyn (c: int array) (n: int): int  = 
  let mem = Array.make (n+1) (-1) in 
  mem.(0) <- 0;
  let rec calculer_decoupe (i: int) : int = 

    if mem.(i) = -1 then begin 
      for k =1 to min i n do
        if c.(k) + calculer_decoupe (i-k) > mem.(i)then
          mem.(i) <-  c.(k) + mem.(i-k);
        done
    end;

    mem.(i);
  in calculer_decoupe n

 let decoupe_prog_dyn (c: int array) (n: int): int * int list = 
  let mem = Array.make (n+1) ((-1),[]) in 
  mem.(0) <- (0, []);
  let rec calculer_decoupe (i: int) : int * int list= 
    if mem.(i) = (-1,[]) then begin 
      for k =1 to min i n do
        let a,l1 = mem.(i) in 
        let b,l2 = calculer_decoupe (i-k) in 
        if c.(k) + b > a then
          mem.(i) <-  (c.(k) + b, k::l2);
        done
    end;

    mem.(i);
  in calculer_decoupe n
  