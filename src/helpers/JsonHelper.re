let emitErrorAsLogAndIgnore = (error: exn) => {
  Js.Console.error(error);
  None;
};

let parseWithoutError = (jsonString: string) : option(Js.Json.t) => 
  try (Some(Json.parseOrRaise(jsonString))) {
  | error => emitErrorAsLogAndIgnore(error);
};

let stringify = (json: Js.Json.t) : string => {
  //TODO: Take care of XSS
  Json.stringify(json) |> String.escaped;
};