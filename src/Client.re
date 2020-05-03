[@bs.scope "window"] [@bs.val] external encodedInitialState : Js.Nullable.t(Js.Json.t) = "__INITIAL_STATE__";
[@bs.scope "window"] [@bs.val] external encodedInitialErrors : Js.Nullable.t(Js.Json.t) = "__INITIAL_ERRORS__";

let flattenDecodedState = (decodedState: Types.result(State.state)) : (option(State.state), option(string)) => {
  switch (decodedState) {
  | Belt.Result.Ok(state) => (Some(state), None)
  | Belt.Result.Error(error) => (None, Some(error))
  };
};

let flattenState = (maybeState: option(Types.result(State.state))) : (option(State.state), option(string)) => {
  switch (maybeState) {
  | Some(decodedState) => flattenDecodedState(decodedState)
  | None => (None, None)
  };
};

let getInitialState = () : option(Types.result(State.state)) => { 
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

    let decodedInitialState: option(Types.result(State.state)) = getInitialState();
    let (initialState: option(State.state), stateDecodeError: option(string)) = flattenState(decodedInitialState);

    let decodedInitialErrors: list(string) = getInitialErrors();
    let initialErrors = 
      switch (stateDecodeError) {
      | Some(error) => [ error, ...decodedInitialErrors ]
      | None => decodedInitialErrors
      };

    React.useEffect0(() => {
      ignore(deleteInitialData());
      None;
    });  

    <App initialState=initialState initialErrors=initialErrors url=url />
  };
};

ReactDOMRe.hydrateToElementWithId(<ClientApp />, "root");
