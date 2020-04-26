open Css;

let commentContainer = style([
  width(px(600)),
  marginLeft(`auto),
  marginRight(`auto),
  marginTop(px(16)),
  border(px(1),`solid,hex("000")),
]);

let commenterName = style([
  fontWeight(`bold),
  fontSize(px(18)),
  marginTop(px(16)),
  marginLeft(px(16)),
  marginRight(px(16)),
  marginBottom(px(4)),
]);

let commentBody = style([
  marginBottom(px(16)),
  marginLeft(px(16)),
  marginRight(px(16)),
]);