type state = {
  posts: list(Types.Posts.post),
  postDetails: option(Types.PostDetails.postDetails)
};

let createState = (~posts=?, ~postDetails=?, ()) : state => {
  {
    posts: GenericHelper.flattenOptionOfList(posts),
    postDetails: postDetails,
  };
};

let decodeStateUnsafe = (json: Js.Json.t) : state => Json.Decode.{
  posts: json |> field("posts", Types.Posts.decodePostsUnsafe),
  postDetails: json |> optional(field("postDetails", Types.PostDetails.decodePostDetailsUnsafe)),
};

let decodeState = (json: Js.Json.t) : Types.result(state) => {
  try (Belt.Result.Ok(decodeStateUnsafe(json))) {
  | _ => Belt.Result.Error("Error in decoding JSON to: state")
  };
};

let encodeState = (stateRecord: state) : Js.Json.t => Json.Encode.(
  object_([
    ("posts", stateRecord.posts |> Types.Posts.encodePosts),
    ("postDetails", stateRecord.postDetails |> nullable(Types.PostDetails.encodePostDetails) ),
  ])
);

let createEmptyState = () : state => createState(());

let createStateFromPosts = (posts: list(Types.Posts.post)) : state => createState(~posts, ());

let createStateFromPostAndComments = (maybePost: option(Types.Posts.post), comments: list(Types.Comments.comment)) : state => {
  switch (maybePost) {
  | Some(post) => createState(~postDetails={ post, comments }, ())
  | None => createEmptyState()
  };
};