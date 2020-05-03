type page = 
  | AllPosts
  | MyPosts
  | Post(Types.Posts.postId)
  | NotFound;

let myPostsURLPrefix = "my-posts";
let postDetailsURLPrefix = "post";
let notFoundURLPrefix = "404";

let pageURL(p: page) = {
  switch (p) {
  | AllPosts => "/"
  | MyPosts => {j|/$myPostsURLPrefix|j}
  | Post(postId) => {j|/$postDetailsURLPrefix/$postId|j}
  | NotFound => {j|/$notFoundURLPrefix|j}
  };
};

let validateIdForPostPage = (postId: string) : page => {
  switch (GenericHelper.parseInt(postId)) {
  | Some(id) => Post(id)
  | None => NotFound
  };
};

let getCorrespondingPage = (url: ReasonReactRouter.url) : page => {
  switch url.path {
  | [] => AllPosts
  | [myPosts] when myPosts === myPostsURLPrefix => MyPosts 
  | [post, id] when post === postDetailsURLPrefix => validateIdForPostPage(id)
  | [notFound] when notFound === notFoundURLPrefix => NotFound
  | _ => NotFound
  };
};