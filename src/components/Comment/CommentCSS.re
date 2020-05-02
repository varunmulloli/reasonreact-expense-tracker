open Css;

let commentContainer = merge([
  Theme.border,
  style([
    marginTop(Theme.marginWidth),
    padding(Theme.paddingWidth),
  ]),
]);

let commenterName = style([
  fontWeight(`bold),
  fontSize(px(18)),
]);

let commentBody = style([
  paddingTop(Theme.paddingWidth),
]);