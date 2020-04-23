let baseURL = "https://jsonplaceholder.typicode.com";

let fetchAllPosts = () : Js.Promise.t(list(Types.Posts.post)) => {
  Js.Promise.(
    APIHelper.makeRequest(baseURL ++ "/posts")
    |> then_(json => json |> Types.Posts.extractPostsFromJson |> resolve)
  );
};