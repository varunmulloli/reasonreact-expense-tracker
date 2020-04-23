type state = {
  posts: list(Types.Posts.post),
};

let createEmptyState = () : state => {
  let initialState: state = {
    posts: [],
  };
  initialState;
};

let createState = (~posts=?, ()) : state => {
  let newPosts = switch posts {
    | Some(p) => p
    | None => []
  };

  let newState: state = {
    posts: newPosts,
  };
  newState;
};

let decodeState = (json: Js.Json.t) : state => Json.Decode.{
  posts: json |> field("posts", Types.Posts.decodePosts),
};

let encodeState = (stateRecord: state) : Js.Json.t => Json.Encode.(
  object_([
    ("posts", stateRecord.posts |> Types.Posts.encodePosts),
  ])
);