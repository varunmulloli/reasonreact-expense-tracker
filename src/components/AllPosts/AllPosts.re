let navigateToPost = (postId: Types.Posts.postId) => {
  ReasonReactRouter.push("/post/" ++ string_of_int(postId))
};

let postComponent = (index: int, post: Types.Posts.post) : React.element => {
  <div className=AllPostsCSS.postContainer onClick=(_ => navigateToPost(post.id)) key=string_of_int(index)>
    <Post post=post />
  </div>
};

[@react.component]
let make = (~postsFromServer: option(list(Types.Posts.post))) => {
  let initialPosts: list(Types.Posts.post) =
    switch postsFromServer {
    | Some(p) => p
    | None => []
    };

  let (posts: list(Types.Posts.post), setPosts) = React.useState(() => initialPosts);
  let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let dataToFetch: option(unit => Js.Promise.t(State.state)) = RouteData.getDataToFetch(page);

  let fetchPostsAndUpdateState = () : Js.Promise.t(unit) => {
    switch (dataToFetch) {
    | Some(fetchData) => Js.Promise.(fetchData() |> then_((state: State.state) => setPosts(_ => state.posts) |> resolve ))
    | None => Js.Promise.resolve(setPosts(_ => []))
    };
  };

  let fetchNewPosts = () => {
    switch postsFromServer {
    | Some(_) => ignore(Js.Promise.resolve())
    | None => ignore(fetchPostsAndUpdateState())
    };
    None;
  };
  
  React.useEffect1(fetchNewPosts, [|url|]);  

  <div>
    {RenderHelper.renderList(posts, postComponent)}
  </div>
};