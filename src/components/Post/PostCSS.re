open Css;

let postContainer = style([
  marginTop(px(16)),
  border(px(1),`solid,hex("000")),
]);

let postTitle = style([
  fontWeight(`bold),
  fontSize(px(18)),
  marginTop(px(16)),
  marginLeft(px(16)),
  marginRight(px(16)),
  marginBottom(px(4)),
]);

let postBody = style([
  marginBottom(px(16)),
  marginLeft(px(16)),
  marginRight(px(16)),
]);