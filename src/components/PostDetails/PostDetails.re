let commentComponent = (index: int, comment: Types.Comments.comment) : React.element => {
  <Comment key=string_of_int(index) comment=comment />
};

let renderPostDetails = (postDetails: Types.PostDetails.postDetails) : React.element => {
  <div className=PostDetailsCSS.postContainer>
    <Post post=postDetails.post />
    <div className=PostDetailsCSS.commentsTitle>{React.string("Comments")}</div>
    {RenderHelper.renderList(postDetails.comments, commentComponent)}
  </div>
};

[@react.component]
let make = (~postDetailsFromServer: option(Types.PostDetails.postDetails)) => {
  let (postDetails, setPostDetails) = React.useState(() => postDetailsFromServer);
  let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let dataToFetch: option(unit => Js.Promise.t(State.state)) = RouteData.getDataToFetch(page);

  let fetchPostDetailsAndUpdateState = () : Js.Promise.t(unit) => {
    switch (dataToFetch) {
    | Some(fetchData) => Js.Promise.(fetchData() |> then_((state: State.state) => setPostDetails(_ => state.postDetails) |> resolve ))
    | None => Js.Promise.resolve(setPostDetails(_ => None))
    };
  };

  let fetchNewPostDetails = () => {
    switch postDetailsFromServer {
    | Some(_) => ignore(Js.Promise.resolve())
    | None => ignore(fetchPostDetailsAndUpdateState())
    };
    None;
  };
  
  React.useEffect1(fetchNewPostDetails, [|url|]);  

  switch (postDetails) {
  | Some(pd) => renderPostDetails(pd)
  | None => React.string("Couldn't find post")
  };
};