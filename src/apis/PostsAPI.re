let fetchAllPosts = () : Js.Promise.t(list(Types.Posts.post)) => {
  Js.Promise.(
    APIHelper.makeRequest(Constants.baseURL ++ "/posts")
    |> then_(json => json |> Types.Posts.extractPostsFromJson |> resolve)
  );
};

let fetchMyPosts = () : Js.Promise.t(list(Types.Posts.post)) => {
  Js.Promise.(
    APIHelper.makeRequest(Constants.baseURL ++ "/posts?userId=3")
    |> then_(json => json |> Types.Posts.extractPostsFromJson |> resolve)
  );
};

let fetchPost = (postId: Types.Posts.postId) : Js.Promise.t(option(Types.Posts.post)) => {
  Js.Promise.(
    APIHelper.makeRequest(Constants.baseURL ++ "/posts/" ++ string_of_int(postId))
    |> then_(json => Belt.Option.map(json, Types.Posts.decodePost) |> resolve)
  );
};