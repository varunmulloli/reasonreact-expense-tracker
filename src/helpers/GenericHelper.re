let parseInt = (s: string) : option(int) => {
try (Some(int_of_string(s))) {
    | _ => None
  };
};

let flattenOptionOfList = (o: option(list('a))) : list('a) => {
  switch o {
  | Some(l) => l
  | None => []
  };
};