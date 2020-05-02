[@bs.scope "window"] [@bs.val] external encodedInitialState : Js.Nullable.t(Js.Json.t) = "__INITIAL_STATE__";
[@bs.scope "window"] [@bs.val] external encodedInitialErrors : Js.Nullable.t(Js.Json.t) = "__INITIAL_ERRORS__";

let getInitialState = () : option(State.state) => { 
  encodedInitialState 
  -> Js.Nullable.toOption 
  -> Belt.Option.map(State.decodeState);
};

let getInitialErrors = () : list(string) => { 
  encodedInitialErrors 
  -> Js.Nullable.toOption 
  -> Belt.Option.map(json => Json.Decode.(json |> list(string)))
  -> GenericHelper.flattenOptionOfList;
};

let deleteInitialData = () => {
  ignore([%raw "delete window.__INITIAL_STATE__"]);
  ignore([%raw "delete window.__INITIAL_ERRORS__"]);
};

module ClientApp = {
  [@react.component]
  let make = () => {
    let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
    let initialState: option(State.state) = getInitialState();
    let initialErrors: list(string) = getInitialErrors();

    React.useEffect0(() => {
      // ignore(deleteInitialData());
      None;
    });  

    <App initialState=initialState initialErrors=initialErrors url=url />
  };
};

ReactDOMRe.hydrateToElementWithId(<ClientApp />, "root");
