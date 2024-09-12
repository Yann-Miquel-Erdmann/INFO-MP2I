let test() = 
  assert(1==1);
  assert(5==5);
  assert(3==1)

let valider (fct:unit->unit): bool  = 
  try fct () = () with
  | Assert_failure _ -> false
  
  
