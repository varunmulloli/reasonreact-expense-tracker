let emitErrorAsLogAndIgnore = (error: exn) => {
  Js.Console.error(error);
  None;
};

//TODO: Use result instead of option
let parseWithoutError = (jsonString: string) : option(Js.Json.t) => 
  try (Some(Json.parseOrRaise(jsonString))) {
  | error => emitErrorAsLogAndIgnore(error);
};