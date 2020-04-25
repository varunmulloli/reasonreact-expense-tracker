let postComponent = (index: int, post: Types.Posts.post) : React.element => {
  <Post key=string_of_int(index) post=post />
};

[@react.component]
let make = (~postsFromServer: option(list(Types.Posts.post)), ~fetchData: option(ReasonReactRouter.url => Js.Promise.t(State.state))) => {
  let initialPosts: list(Types.Posts.post) = switch postsFromServer {
    | Some(p) => p
    | None => []
  };

  let (posts: list(Types.Posts.post), setPosts) = React.useState(() => initialPosts);
  let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();

  let fetchPostsAndUpdateState = () => switch(fetchData) {
    | Some(f) => Js.Promise.(f(url) |> then_((state: State.state) => setPosts(_ => state.posts) |> resolve ))
    | None => setPosts(_ => []) |> Js.Promise.resolve
  };

  React.useEffect1(() => {
    switch postsFromServer {
    | Some(_) => ignore(Js.Promise.resolve())
    | None => ignore(fetchPostsAndUpdateState())
    };
    None;
  }, [|url|]);  

  <div>
    {RenderHelper.renderList(posts, postComponent)}
  </div>
};