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

let renderHTML = (res: Express.Response.t, urlJson: Js.Json.t, dataJson: option(Js.Json.t)) => {
  let stringifyJson = (json: Js.Json.t) : string => json |> Json.stringify |> Js.String.replaceByRe([%re "/</g"],"\\u003c");
  let initialState: option(string) = Belt.Option.map(dataJson, stringifyJson);
  let initialURL = stringifyJson(urlJson);
  let content = ReactDOMServerRe.renderToString(<App initialState=initialState initialURL=Some(initialURL) />);
  let htmlContent = Template.make(~content, ~initialState, ~initialURL, ());
  Express.Response.sendString(htmlContent, res);
};

let loadDataAndRenderHTML = (_next, _req, res) : Js.Promise.t(Express.complete) => {
  let url: ReasonReactRouter.url = extractURLFromRequest(_req);
  let urlJson: Js.Json.t = JsonHelper.encodeURL(url);
  let routeConfig: Routes.routeConfig = Routes.getRouteConfig(url);

  switch(routeConfig.loadData) {
    | Some(loadData) => Js.Promise.(loadData() |> then_(json => json |> renderHTML(res, urlJson) |> Js.Promise.resolve ))
    | None => None |> renderHTML(res, urlJson) |> Js.Promise.resolve
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