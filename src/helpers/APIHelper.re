[%raw "require('isomorphic-fetch')"];

let makeRequest = (url: string) => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(jsonResponse => Js.Promise.resolve(Some(jsonResponse)))
    |> catch(_err => Js.Promise.resolve(None))
  );
}

