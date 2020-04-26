let fetchAllPosts = () : Js.Promise.t(State.state) => {
  Js.Promise.(PostsAPI.fetchAllPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
};

let fetchMyPosts = () : Js.Promise.t(State.state) => {
  Js.Promise.(PostsAPI.fetchMyPosts() |> then_(posts => posts |> State.createStateFromPosts |> resolve));
};

let fetchPostAndComments = (postId: Types.Posts.postId) : Js.Promise.t(State.state) => {
  let postPromise = PostsAPI.fetchPost(postId);
  let commentsPromise = CommentsAPI.fetchCommentsForPost(postId);
  let promises = (postPromise, commentsPromise);
  Js.Promise.all2(promises)
  |> Js.Promise.then_(((post, comments)) => State.createStateFromPostAndComments(post, comments) |> Js.Promise.resolve)
};

let fetchPostsAndCommentsForValidPostId = (postId: option(Types.Posts.postId)) => () : Js.Promise.t(State.state) => {
  switch (postId) {
  | Some(id) => fetchPostAndComments(id)
  | None => Js.Promise.resolve(State.createEmptyState())
  };
};

let getDataToFetch = (page: RoutePage.page) : option(unit => Js.Promise.t(State.state)) => {
  switch page {
  | RoutePage.AllPosts => Some(fetchAllPosts)
  | RoutePage.MyPosts => Some(fetchMyPosts)
  | RoutePage.Post(id) => Some(fetchPostsAndCommentsForValidPostId(id))
  | RoutePage.NotFound => None
  };
};
