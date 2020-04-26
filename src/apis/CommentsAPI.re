let fetchCommentsForPost = (postId: Types.Posts.postId) : Js.Promise.t(list(Types.Comments.comment)) => {
  Js.Promise.(
    APIHelper.makeRequest(Constants.baseURL ++ "/posts/" ++ string_of_int(postId) ++ "/comments" )
    |> then_(json => json |> Types.Comments.extractCommentsFromJson |> resolve)
  );
};