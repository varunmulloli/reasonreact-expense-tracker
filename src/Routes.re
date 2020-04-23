type routeConfig = {
  component: State.state => React.element,
  fetchData: option(ReasonReactRouter.url => Js.Promise.t(State.state)),
};

module type Route = {
  let renderComponent: State.state => React.element;
  let fetchInitialData: ReasonReactRouter.url => Js.Promise.t(State.state);
};

module AllPostsRoute: Route = {
  let renderComponent = (state: State.state) : React.element => {
    <AllPosts posts=state.posts />
  };

  let fetchInitialData = _ : Js.Promise.t(State.state) => {
    let createStateFromPosts = (posts: list(Types.Posts.post)) => State.createState(~posts=posts, ());
    Js.Promise.(PostsAPI.fetchAllPosts() |> then_(posts => posts |> createStateFromPosts |> resolve));
  };
};

let getRouteConfig = (url: ReasonReactRouter.url) : routeConfig =>  switch url.path {
  | [] => { component: AllPostsRoute.renderComponent, fetchData: Some(AllPostsRoute.fetchInitialData) }
  | _ => { component: _ => <NotFound />, fetchData: None }
};