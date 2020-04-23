let postComponent = (index: int, post: Types.Posts.post) : React.element => {
  <Post key=string_of_int(index) post=post />
};

[@react.component]
let make = (~posts: list(Types.Posts.post)) => {
  <div>
    {RenderHelper.renderList(posts, postComponent)}
  </div>
};