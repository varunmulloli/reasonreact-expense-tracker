[%raw "require('isomorphic-fetch')"];

let makeRequest = (url: string) : Types.future(Js.Json.t) => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_((res: Fetch.Response.t) => Fetch.Response.ok(res) ? Fetch.Response.json(res) : Js.Exn.raiseError(Fetch.Response.statusText(res)))
    |> then_((json: Js.Json.t) => resolve(Belt.Result.Ok(json)))
    |> catch(_ => resolve(Belt.Result.Error("Error in fetching data: " ++ url)))
  );
};
