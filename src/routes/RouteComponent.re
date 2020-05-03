let renderPosts = (maybeState: option(State.state), errors: list(string)) : React.element => {
  switch maybeState {
  | Some(state) => <AllPosts postsFromServer=Some(state.posts) errorsFromServer=errors />
  | None => <AllPosts postsFromServer=None errorsFromServer=errors />
  };
};

let renderPostAndComments = (maybeState: option(State.state), errors: list(string)) : React.element => {
  switch maybeState {
  | Some(state) => <PostDetails postDetailsFromServer=state.postDetails errorsFromServer=errors />
  | None => <PostDetails postDetailsFromServer=None errorsFromServer=errors />
  };
};

let getComponentToRender = (page: RoutePage.page) : ((option(State.state), list(string)) => React.element) => {
  switch page {
  | RoutePage.AllPosts => renderPosts
  | RoutePage.MyPosts => renderPosts
  | RoutePage.Post(_) => renderPostAndComments
  | RoutePage.NotFound => (_,_) => <NotFound />
  };
};