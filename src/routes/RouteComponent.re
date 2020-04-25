let renderPosts = (maybeState: option(State.state)) : React.element => {
  switch maybeState {
  | Some(state) => <AllPosts postsFromServer=Some(state.posts) />
  | None => <AllPosts postsFromServer=None />
  };
};

let getComponentToRender = (page: RoutePage.page) : (option(State.state) => React.element) => {
  switch page {
  | RoutePage.AllPosts => renderPosts
  | RoutePage.MyPosts => v
  | RoutePage.NotFound => _ => <NotFound />
  };
};