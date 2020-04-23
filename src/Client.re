[@bs.scope "window"] [@bs.val] external encodedInitialState : Js.Nullable.t(string) = "__INITIAL_STATE__";

let extractedInitialState: option(State.state) = 
  encodedInitialState 
  -> Js.Nullable.toOption 
  -> Belt.Option.flatMap(JsonHelper.parseWithoutError)
  -> Belt.Option.map(State.decodeState);

let initialState: State.state = switch extractedInitialState {
  | Some(state) => state
  | None => State.createEmptyState()
};

ReactDOMRe.hydrateToElementWithId(<App initialState=initialState />, "root");