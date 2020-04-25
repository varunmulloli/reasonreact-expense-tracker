type routeConfig = {
  component: option(State.state) => React.element,
  fetchData: option(ReasonReactRouter.url => Js.Promise.t(State.state)),
  activeRoute: Types.ActiveRoute.activeRoute,
};

module type Route = {
  let renderComponent: option(State.state) => React.element;
  let fetchInitialData: ReasonReactRouter.url => Js.Promise.t(State.state);
};

module AllPostsRoute: Route = {
  let fetchInitialData = (_: ReasonReactRouter.url) : Js.Promise.t(State.state) => {
    Js.Promise.(PostsAPI.fetchAllPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
  };

  let renderComponent = (state: option(State.state)) : React.element => switch state {
    | Some(s) => <AllPosts postsFromServer=Some(s.posts) fetchData=Some(fetchInitialData) />
    | None => <AllPosts postsFromServer=None fetchData=Some(fetchInitialData) />
  };
};

module MyPostsRoute: Route = {
  let fetchInitialData = (_: ReasonReactRouter.url) : Js.Promise.t(State.state) => {
    Js.Promise.(PostsAPI.fetchMyPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
  };

  let renderComponent = (state: option(State.state)) : React.element => switch state {
    | Some(s) => <AllPosts postsFromServer=Some(s.posts) fetchData=Some(fetchInitialData) />
    | None => <AllPosts postsFromServer=None fetchData=Some(fetchInitialData) />
  };
};

let getRouteConfig = (url: ReasonReactRouter.url) : routeConfig =>  switch url.path {
  | [] => { 
            component: AllPostsRoute.renderComponent, 
            fetchData: Some(AllPostsRoute.fetchInitialData), 
            activeRoute: Types.ActiveRoute.AllPosts 
          }
  | ["my-posts"] => { 
                      component: MyPostsRoute.renderComponent, 
                      fetchData: Some(MyPostsRoute.fetchInitialData), 
                      activeRoute: Types.ActiveRoute.MyPosts 
                    }
  | _ =>  { 
            component: _ => <NotFound />, 
            fetchData: None, 
            activeRoute: Types.ActiveRoute.Others 
          }
};