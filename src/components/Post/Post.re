[@react.component]
let make = (~post: Types.Posts.post) => {
  <div className=PostCSS.postContainer>
    <div className=PostCSS.postTitle>
      {React.string(post.title)}
    </div>
    <div className=PostCSS.postBody>
      {React.string(post.body)}
    </div>
  </div>
};