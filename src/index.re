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

let renderHTML = (res: Express.Response.t, url: ReasonReactRouter.url, initialState: State.state) => {
  let content = ReactDOMServerRe.renderToString(<App initialState=Some(initialState) url=url />);
  let contentWithStyles = renderStylesToString(content);
  let encodedInitialState: string = initialState |> State.encodeState |> JsonHelper.stringify;
  let htmlContent = Template.make(~content=contentWithStyles, ~initialState=encodedInitialState, ());
  Express.Response.sendString(htmlContent, res);
};

let loadDataAndRenderHTML = (_next, _req, res) : Js.Promise.t(Express.complete) => {
  let url: ReasonReactRouter.url = extractURLFromRequest(_req);
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let dataToFetch: option(unit => Js.Promise.t(State.state)) = RouteData.getDataToFetch(page);

  switch(dataToFetch) {
    | Some(fetchData) => Js.Promise.(fetchData() |> then_(state => state |> renderHTML(res, url) |> Js.Promise.resolve ))
    | None => State.createEmptyState() |> renderHTML(res, url) |> Js.Promise.resolve
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