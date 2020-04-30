open Css;

let postContainer = merge([
  Theme.border,
  style([
    padding(Theme.paddingWidth),
  ]),
]);

let postTitle = style([
  fontWeight(`bold),
  fontSize(px(18)),
]);

let postBody = style([
  paddingTop(Theme.paddingWidth),
]);