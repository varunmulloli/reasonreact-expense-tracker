[@react.component]
let make = (~comment: Types.Comments.comment) => {
  <div className=CommentCSS.commentContainer>
    <div className=CommentCSS.commenterName>
      {React.string(comment.name)}
    </div>
    <div className=CommentCSS.commentBody>
      {React.string(comment.body)}
    </div>
  </div>
};