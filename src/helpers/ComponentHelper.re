type setData = State.state => unit;
type setErrors = Types.setState(list(string));
type setDataState = Types.setState(Types.dataState);

let renderList = (listOfItems: list('a), component: (int, 'a) => React.element) : React.element => {
  listOfItems |> List.mapi(component) |> Array.of_list |> ReasonReact.array;
};

let fetchDataAndUpdateState = (url: ReasonReactRouter.url, setData: setData, setDataState: setDataState, setErrors: setErrors) : Js.Promise.t(unit) => {
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let dataToFetch: option(unit => Js.Promise.t(Types.uidata(State.state))) = RouteData.getDataToFetch(page);
  
  let setComponentStates = ((state: State.state, errors: list(string))) : Js.Promise.t(unit) => {
    setData(state);
    setErrors(_ => errors);
    setDataState(_ => Types.Loaded);
    Js.Promise.resolve();
  };

  let fetchDataAndSetComponentState = (fetchData: unit => Js.Promise.t(Types.uidata(State.state))) : Js.Promise.t(unit) => {
    setDataState(_ => Types.Loading);
    fetchData() |> Js.Promise.then_(setComponentStates);
  };

  switch (dataToFetch) {
  | Some(fetchData) => fetchDataAndSetComponentState(fetchData)
  | None => Js.Promise.resolve()
  };
};