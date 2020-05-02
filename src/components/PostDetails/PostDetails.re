let commentComponent = (index: int, comment: Types.Comments.comment) : React.element => {
  <Comment key=string_of_int(index) comment=comment />
};

let renderPostDetailsComponent = (postDetails: Types.PostDetails.postDetails) : React.element => {
  <div className=PostDetailsCSS.postContainer>
    <Post post=postDetails.post />
    <div className=PostDetailsCSS.commentsTitle>{React.string("Comments")}</div>
    {ComponentHelper.renderList(postDetails.comments, commentComponent)}
  </div>
};

let renderPostDetails = (maybePostDetails: option(Types.PostDetails.postDetails)) : React.element => {
  switch (maybePostDetails) {
  | Some(postDetails) => renderPostDetailsComponent(postDetails)
  | None => React.string("Couldn't find post")
  };
};

[@react.component]
let make = (~postDetailsFromServer: option(Types.PostDetails.postDetails)) => {
  let url: ReasonReactRouter.url = ReasonReactRouter.useUrl();
  
  let (dataState: Types.dataState, setDataState: Types.setState(Types.dataState)) = React.useState(() => Types.Loaded);
  let (errors: list(string), setErrors: Types.setState(list(string))) = React.useState(() => []);
  let (postDetails: option(Types.PostDetails.postDetails), setPostDetails: Types.setState(option(Types.PostDetails.postDetails))) = React.useState(() => postDetailsFromServer);
  
  let setPostDetailsFromState = (state: State.state) : unit => setPostDetails(_ => state.postDetails);
  
  React.useEffect1(() => {
    switch postDetailsFromServer {
    | Some(_) => ignore(Js.Promise.resolve())
    | None => ignore(ComponentHelper.fetchDataAndUpdateState(url, setPostDetailsFromState, setDataState, setErrors))
    };
    None;
  }, [|url|]);  

  switch (dataState) {
  | Loading => React.string("Loading...")
  | Loaded => renderPostDetails(postDetails);
  };
};