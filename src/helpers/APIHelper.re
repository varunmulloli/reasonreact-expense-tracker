[%raw "require('isomorphic-fetch')"];

type response = Js.Promise.t(option(Js.Json.t));

//TODO: Log error
let makeRequest = (url: string) : response => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(jsonResponse => Js.Promise.resolve(Some(jsonResponse)))
    |> catch(_err => Js.Promise.resolve(None))
  );
};
