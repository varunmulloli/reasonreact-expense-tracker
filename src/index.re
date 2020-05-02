[@bs.module "emotion-server"] external renderStylesToString : string => string = "renderStylesToString";

let app = Express.App.make();

let extractURLFromRequest = (req: Express.Request.t) : ReasonReactRouter.url => {
  let path: list(string) = req |> Express.Request.path |> Js.String.split("/") |> Array.to_list |> List.filter(i => i !== "");
  let originalUrl: string = Express.Request.originalUrl(req);
  let queryParams: string = switch(Js.String.indexOf("?", originalUrl)) {
    | -1 => ""
    | index => Js.String.slice(~from=index+1, ~to_=Js.String.length(originalUrl), originalUrl)
  };
  { path: path, hash: "", search: queryParams };
}

let renderHTML = (res: Express.Response.t, url: ReasonReactRouter.url, initialState: State.state, initialErrors: list(string)) => {
  let content: string = ReactDOMServerRe.renderToString(<App initialState=Some(initialState) initialErrors=initialErrors url=url />);
  let contentWithStyles: string = renderStylesToString(content);
  let encodedInitialState: Js.Json.t = initialState |> State.encodeState;
  let encodedInitialErrors: Js.Json.t = Json.Encode.(initialErrors |> list(string));
  let htmlContent: string = Template.make(~content=contentWithStyles, ~initialState=encodedInitialState, ~initialErrors=encodedInitialErrors, ());
  Express.Response.sendString(htmlContent, res);
};

let loadDataAndRenderHTML = (_next, _req, res) : Js.Promise.t(Express.complete) => {
  let url: ReasonReactRouter.url = extractURLFromRequest(_req);
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let dataToFetch: option(unit => Js.Promise.t(Types.uidata(State.state))) = RouteData.getDataToFetch(page);

  switch(dataToFetch) {
    | Some(fetchData) => Js.Promise.(fetchData() |> then_(((state: State.state, errors: list(string))) => renderHTML(res, url, state, errors) |> resolve ))
    | None => renderHTML(res, url, State.createEmptyState(), []) |> Js.Promise.resolve
  };
};

Express.Static.defaultOptions()
|> Express.Static.make("dist/")
|> Express.Static.asMiddleware
|> Express.App.useOnPath(app, ~path="/dist");

loadDataAndRenderHTML
|> Express.PromiseMiddleware.from
|> Express.App.useOnPath(~path="/", app);

let port = 3000;

let onListen = e => switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log("listening at localhost:" ++ string_of_int(port))
};

Express.App.listen(app, ~onListen, ~port, ());