let decodePostsFromJson = (json: Types.result(Js.Json.t)) : Types.future(list(Types.Posts.post)) => {
  Belt.Result.flatMap(json, Types.Posts.decodePosts) |> Js.Promise.resolve;
};

let decodePostFromJson = (json: Types.result(Js.Json.t)) : Types.future(Types.Posts.post) => {
  Belt.Result.flatMap(json, Types.Posts.decodePost) |> Js.Promise.resolve;
};

let fetchAllPosts = () : Types.future(list(Types.Posts.post)) => {
  APIHelper.makeRequest(Constants.baseURL ++ "/posts") 
  |> Js.Promise.then_(decodePostsFromJson);
};

let fetchPostsForUser = (userId: Types.Posts.userId) : Types.future(list(Types.Posts.post)) => {
  APIHelper.makeRequest(Constants.baseURL ++ "/posts?userId=" ++ string_of_int(userId)) 
  |> Js.Promise.then_(decodePostsFromJson);
};

let fetchPost = (postId: Types.Posts.postId) : Types.future(Types.Posts.post) => {
  APIHelper.makeRequest(Constants.baseURL ++ "/posts/" ++ string_of_int(postId)) 
  |> Js.Promise.then_(decodePostFromJson);
};