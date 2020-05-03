let decodeCommentsFromJson = (json: Types.result(Js.Json.t)) : Types.future(list(Types.Comments.comment)) => {
  Belt.Result.flatMap(json, Types.Comments.decodeComments) |> Js.Promise.resolve;
};

let fetchCommentsForPost = (postId: Types.Posts.postId) : Types.future(list(Types.Comments.comment)) => {
  APIHelper.makeRequest(Constants.baseURL ++ "/posts/" ++ string_of_int(postId) ++ "/comments" )
  |> Js.Promise.then_(decodeCommentsFromJson);
};