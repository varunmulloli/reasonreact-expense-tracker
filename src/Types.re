type result('a) = Belt.Result.t('a, string);
type future('a) = Js.Promise.t(result('a));
type uidata('a) = ('a, list(string));

type dataState = 
| Loading
| Loaded;

type setState('a) = ('a => 'a) => unit;

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

  let decodePostUnsafe = (json: Js.Json.t) : post => Json.Decode.{
    userId: json |> field("userId", int),
    id: json |> field("id", int),
    title: json |> field("title", string),
    body: json |> field("body", string),
  };

  let decodePost = (json: Js.Json.t) : result(post) => {
    try (Belt.Result.Ok(decodePostUnsafe(json))) {
    | _ => Belt.Result.Error("Error in decoding JSON to: post")
    };
  };

  let encodePost = (postItem: post) : Js.Json.t => Json.Encode.(
    object_([
      ("userId", int(postItem.userId)),
      ("id", int(postItem.id)),
      ("title", string(postItem.title)),
      ("body", string(postItem.body)),
    ])
  );

  let decodePostsUnsafe = (json: Js.Json.t) : list(post) => Json.Decode.(
    json |> list(decodePostUnsafe)
  );

  let decodePosts = (json: Js.Json.t) : result(list(post)) => {
    try (Belt.Result.Ok(decodePostsUnsafe(json))) {
    | _ => Belt.Result.Error("Error in decoding JSON to: list(post)")
    };
  };

  let encodePosts = (posts: list(post)) : Js.Json.t => Json.Encode.(
    posts |> list(encodePost)
  );
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

  let decodeCommentUnsafe = (json: Js.Json.t) : comment => Json.Decode.{
    postId: json |> field("postId", int),
    id: json |> field("id", int),
    name: json |> field("name", string),
    email: json |> field("email", string),
    body: json |> field("body", string),
  };

  let decodeComment = (json: Js.Json.t) : result(comment) => {
    try (Belt.Result.Ok(decodeCommentUnsafe(json))) {
    | _ => Belt.Result.Error("Error in decoding JSON to: comment")
    };
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

  let decodeCommentsUnsafe = (json: Js.Json.t) : list(comment) => Json.Decode.(
    json |> list(decodeCommentUnsafe)
  );

  let decodeComments = (json: Js.Json.t) : result(list(comment)) => {
    try (Belt.Result.Ok(decodeCommentsUnsafe(json))) {
    | _ => Belt.Result.Error("Error in decoding JSON to: list(comment)")
    };
  };

  let encodeComments = (posts: list(comment)) : Js.Json.t => Json.Encode.(
    posts |> list(encodeComment)
  );
};

module PostDetails = {
  type postDetails = {
    post: Posts.post,
    comments: list(Comments.comment),
  };

  let decodePostDetailsUnsafe = (json: Js.Json.t) : postDetails => Json.Decode.{
    post: json |> field("post", Posts.decodePostUnsafe),
    comments: json |> field("comments", Comments.decodeCommentsUnsafe),
  };

  let decodePostDetails = (json: Js.Json.t) : result(postDetails) => {
    try (Belt.Result.Ok(decodePostDetailsUnsafe(json))) {
    | _ => Belt.Result.Error("Error in decoding JSON to: postDetails")
    };
  };

  let encodePostDetails = (postDetailsItem: postDetails) : Js.Json.t => Json.Encode.(
    object_([
      ("post", postDetailsItem.post |> Posts.encodePost),
      ("comments", postDetailsItem.comments |> Comments.encodeComments),
    ])
  );
};

