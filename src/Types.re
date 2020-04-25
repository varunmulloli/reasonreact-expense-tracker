module ActiveRoute = {
  type activeRoute = 
  | AllPosts
  | MyPosts
  | Others;
};

module Posts = {
  type post = {
    userId: int,
    id: int,
    title: string,
    body: string,
  };

  let decodePost = (json: Js.Json.t) : post => Json.Decode.{
    userId: json |> field("userId", int),
    id: json |> field("id", int),
    title: json |> field("title", string),
    body: json |> field("body", string),
  };

  let encodePost = (postItem: post) : Js.Json.t => Json.Encode.(
    object_([
      ("userId", int(postItem.userId)),
      ("id", int(postItem.id)),
      ("title", string(postItem.title)),
      ("body", string(postItem.body)),
    ])
  );

  let decodePosts = (json: Js.Json.t) : list(post) => Json.Decode.(
    json |> list(decodePost)
  );

  let encodePosts = (posts: list(post)) : Js.Json.t => Json.Encode.(
    posts |> list(encodePost)
  );

  let extractPostsFromJson = (json: option(Js.Json.t)): list(post) => {
    let maybePosts: option(list(post)) = Belt.Option.map(json, decodePosts);
    switch maybePosts {
      | Some(p) => p
      | None => []
    };
  };
};


