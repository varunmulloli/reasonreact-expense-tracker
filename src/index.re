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

let renderHTML = (_next, _req, res) => {
  let content = ReactDOMServerRe.renderToString(<App />);
  let htmlContent = Template.make(~content, ());
  let url = extractURLFromRequest(_req);
  Js.log(url);

  Express.Response.sendString(htmlContent, res);
};

Express.Static.defaultOptions()
|> Express.Static.make("dist/")
|> Express.Static.asMiddleware
|> Express.App.useOnPath(app, ~path="/dist");

renderHTML
|> Express.Middleware.from
|> Express.App.useOnPath(~path="/", app);


let port = 3000;

let onListen = e => switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log("listening at localhost:" ++ string_of_int(port))
};

Express.App.listen(app, ~onListen, ~port, ());