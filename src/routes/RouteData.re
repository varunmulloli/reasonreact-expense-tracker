let fetchAllPosts = (_: ReasonReactRouter.url) : Js.Promise.t(State.state) => {
  Js.Promise.(PostsAPI.fetchAllPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
};

let fetchMyPosts = (_: ReasonReactRouter.url) : Js.Promise.t(State.state) => {
  Js.Promise.(PostsAPI.fetchMyPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
};

let getDataToFetch = (page: RoutePage.page) : (option(ReasonReactRouter.url => Js.Promise.t(State.state))) => {
  switch page {
  | RoutePage.AllPosts => Some(fetchAllPosts)
  | RoutePage.MyPosts => Some(fetchMyPosts)
  | RoutePage.NotFound => None
  };
};
