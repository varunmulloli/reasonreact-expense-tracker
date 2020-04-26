let renderPosts = (maybeState: option(State.state)) : React.element => {
  switch maybeState {
  | Some(state) => <AllPosts postsFromServer=Some(state.posts) />
  | None => <AllPosts postsFromServer=None />
  };
};

let renderPostAndComments = (maybeState: option(State.state)) : React.element => {
  switch maybeState {
  | Some(state) => <PostDetails postDetailsFromServer=state.postDetails />
  | None => <PostDetails postDetailsFromServer=None />
  };
};

let getComponentToRender = (page: RoutePage.page) : (option(State.state) => React.element) => {
  switch page {
  | RoutePage.AllPosts => renderPosts
  | RoutePage.MyPosts => renderPosts
  | RoutePage.Post(_) => renderPostAndComments
  | RoutePage.NotFound => _ => <NotFound />
  };
};