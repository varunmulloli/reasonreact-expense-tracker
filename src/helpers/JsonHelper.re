let encodeURL = (url: ReasonReactRouter.url) : Js.Json.t => Json.Encode.(
  object_([
    ("path", url.path |> list(string)),
    ("hash", string(url.hash)),
    ("search", string(url.search)),
  ])
);