module Posts = {
  type userId = int;
  type postId = int;
  type postTitle = string;
  type postBody = string;

  type post = {
    userId: userId,
    id: postId,
    title: postTitle,
    body: postBody,
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

module Comments = {
  type commentId = int;
  type commenterName = string;
  type commenterEmail = string;
  type commentBody = string;

  type comment = {
    postId: Posts.postId,
    id: commentId,
    name: commenterName,
    email: commenterEmail,
    body: commentBody,
  };

  let decodeComment = (json: Js.Json.t) : comment => Json.Decode.{
    postId: json |> field("postId", int),
    id: json |> field("id", int),
    name: json |> field("name", string),
    email: json |> field("email", string),
    body: json |> field("body", string),
  };

  let encodeComment = (commentItem: comment) : Js.Json.t => Json.Encode.(
    object_([
      ("postId", int(commentItem.postId)),
      ("id", int(commentItem.id)),
      ("name", string(commentItem.name)),
      ("email", string(commentItem.email)),
      ("body", string(commentItem.body)),
    ])
  );

  let decodeComments = (json: Js.Json.t) : list(comment) => Json.Decode.(
    json |> list(decodeComment)
  );

  let encodeComments = (posts: list(comment)) : Js.Json.t => Json.Encode.(
    posts |> list(encodeComment)
  );

  let extractCommentsFromJson = (json: option(Js.Json.t)): list(comment) => {
    let maybeComments: option(list(comment)) = Belt.Option.map(json, decodeComments);
    switch maybeComments {
      | Some(c) => c
      | None => []
    };
  };
};

module PostDetails = {
  type postDetails = {
    post: Posts.post,
    comments: list(Comments.comment),
  };

  let decodePostDetails = (json: Js.Json.t) : postDetails => Json.Decode.{
    post: json |> field("post", Posts.decodePost),
    comments: json |> field("comments", Comments.decodeComments),
  };

  let encodePostDetails = (postDetailsItem: postDetails) : Js.Json.t => Json.Encode.(
    object_([
      ("post", postDetailsItem.post |> Posts.encodePost),
      ("comments", postDetailsItem.comments |> Comments.encodeComments),
    ])
  );
};

