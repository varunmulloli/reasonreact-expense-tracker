[@bs.scope "window"] [@bs.val] external encodedInitialState : Js.Nullable.t(string) = "__INITIAL_STATE__";

let getInitialState = () => { 
  encodedInitialState 
  -> Js.Nullable.toOption 
  -> Belt.Option.flatMap(JsonHelper.parseWithoutError)
  -> Belt.Option.map(State.decodeState);
};

let deleteInitialState = () => {
  [%raw "delete window.__INITIAL_STATE__"];
};

module ClientApp = {
  [@react.component]
  let make = () => {
    let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
    let initialState: option(State.state) = getInitialState();

    React.useEffect0(() => {
      ignore(deleteInitialState());
      None;
    });  

    <App initialState=initialState url=url />
  };
};

ReactDOMRe.hydrateToElementWithId(<ClientApp />, "root");
