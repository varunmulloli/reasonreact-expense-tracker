type resultPost = Types.result(Types.Posts.post);
type resultPosts = Types.result(list(Types.Posts.post));
type resultComments = Types.result(list(Types.Comments.comment));

let flattenResult = (result: Types.result(State.state)) : Types.uidata(State.state) => {
  switch (result) {
  | Ok(state) => (state, [])
  | Error(error) => (State.createEmptyState(), [error])
  };
};

let createStateFromPosts = (posts: resultPosts) : Js.Promise.t(Types.uidata(State.state)) => {
  Belt.Result.map(posts, State.createStateFromPosts) |> flattenResult |> Js.Promise.resolve;
};

let createStateFromPostAndComments = ((post: resultPost, comments: resultComments)) : Js.Promise.t(Types.uidata(State.state)) => {
  let stateWithErrors: Types.uidata(State.state) = 
    switch ((post, comments)) {
    | (Belt.Result.Ok(p), Belt.Result.Ok(c)) => (State.createStateFromPostAndComments(Some(p), c), [])
    | (Belt.Result.Ok(p), Belt.Result.Error(ec)) => (State.createStateFromPostAndComments(Some(p), []), [ec])
    | (Belt.Result.Error(ep), Belt.Result.Ok(c)) => (State.createStateFromPostAndComments(None, c), [ep])
    | (Belt.Result.Error(ep), Belt.Result.Error(ec)) => (State.createEmptyState(), [ep, ec])
    };
  Js.Promise.resolve(stateWithErrors);
};

let fetchAllPosts = () : Js.Promise.t(Types.uidata(State.state)) => {
  PostsAPI.fetchAllPosts() |> Js.Promise.then_(createStateFromPosts);
};

let fetchMyPosts = () : Js.Promise.t(Types.uidata(State.state)) => {
  PostsAPI.fetchPostsForUser(3) |> Js.Promise.then_(createStateFromPosts);
};

let fetchPostAndComments = (postId: Types.Posts.postId) : Js.Promise.t(Types.uidata(State.state)) => {
  let postPromise = PostsAPI.fetchPost(postId);
  let commentsPromise = CommentsAPI.fetchCommentsForPost(postId);
  let promises = (postPromise, commentsPromise);
  Js.Promise.all2(promises) |> Js.Promise.then_(createStateFromPostAndComments);
};

let fetchPostsAndCommentsForValidPostId = (postId: option(Types.Posts.postId)) => () : Js.Promise.t(Types.uidata(State.state)) => {
  switch (postId) {
  | Some(id) => fetchPostAndComments(id)
  | None => Js.Promise.resolve((State.createEmptyState(), ["No postId or invalid postId supplied"]))
  };
};

let getDataToFetch = (page: RoutePage.page) : option(unit => Js.Promise.t(Types.uidata(State.state))) => {
  switch page {
  | RoutePage.AllPosts => Some(fetchAllPosts)
  | RoutePage.MyPosts => Some(fetchMyPosts)
  | RoutePage.Post(id) => Some(fetchPostsAndCommentsForValidPostId(id))
  | RoutePage.NotFound => None
  };
};
