let renderList = (listOfItems: list('a), component: (int, 'a) => React.element) : React.element => {
  listOfItems |> List.mapi(component) |> Array.of_list |> ReasonReact.array;
};