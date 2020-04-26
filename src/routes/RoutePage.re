type page = 
  | AllPosts
  | MyPosts
  | Post(option(Types.Posts.postId))
  | NotFound;

let getCorrespondingPage = (url: ReasonReactRouter.url) : page => {
  switch url.path {
  | [] => AllPosts
  | ["my-posts"] => MyPosts 
  | ["post", id] => Post(GenericHelper.parseInt(id))
  | _ =>  NotFound 
  };
};