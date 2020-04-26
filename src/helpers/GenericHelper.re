let parseInt = (s: string) : option(int) => {
try (Some(int_of_string(s))) {
    | _ => None
  };
};