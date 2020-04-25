type page = 
  | AllPosts
  | MyPosts
  | NotFound;

let getCorrespondingPage = (url: ReasonReactRouter.url) : page => {
  switch url.path {
  | [] => AllPosts
  | ["my-posts"] => MyPosts 
  | _ =>  NotFound 
  };
};