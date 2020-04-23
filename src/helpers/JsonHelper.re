let emitErrorAsLogAndIgnore = (error: exn) => {
  Js.Console.error(error);
  None;
};

let parseWithoutError = (jsonString: string) : option(Js.Json.t) => 
  try (Some(Json.parseOrRaise(jsonString))) {
  | error => emitErrorAsLogAndIgnore(error);
};

let stringify = (json: Js.Json.t) : string => {
  Json.stringify(json) 
  |> Js.String.replace("<","\\u003c") 
  |> Js.String.replace(">","\\u003e") 
  |> Js.String.replace("/","\\u002f") 
  |> String.escaped;
};