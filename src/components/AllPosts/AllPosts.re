let navigateToPost = (postId: Types.Posts.postId) => {
  RoutePage.Post(postId) |> RoutePage.pageURL |> ReasonReactRouter.push;
};

let postComponent = (index: int, post: Types.Posts.post) : React.element => {
  <div className=AllPostsCSS.postContainer onClick=(_ => navigateToPost(post.id)) key=string_of_int(index)>
    <Post post=post />
  </div>
};

[@react.component]
let make = (~postsFromServer: option(list(Types.Posts.post)), ~errorsFromServer: list(string)) => {
  let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
  let initialPosts: list(Types.Posts.post) = GenericHelper.flattenOptionOfList(postsFromServer);

  let (dataState: Types.dataState, setDataState: Types.setState(Types.dataState)) = React.useState(() => Types.Loaded);
  let (errors: list(string), setErrors: Types.setState(list(string))) = React.useState(() => errorsFromServer);
  let (posts: list(Types.Posts.post), setPosts: Types.setState(list(Types.Posts.post))) = React.useState(() => initialPosts);
  
  let setPostsFromState = (state: State.state) : unit => setPosts(_ => state.posts);
  
  React.useEffect1(() => {
    switch postsFromServer {
    | Some(_) => ignore(Js.Promise.resolve())
    | None => ignore(ComponentHelper.fetchDataAndUpdateState(url, setPostsFromState, setDataState, setErrors))
    };
    None;
  }, [|url|]);  

  <>
    {
      switch (dataState) {
      | Types.Loading => React.string("Loading...")
      | Types.Loaded => ComponentHelper.renderList(posts, postComponent)
      };
    }
    <Errors errors=errors />
  </>
};