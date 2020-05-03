open Css;

let errorContainer = style([
  width(px(250)),
  position(`absolute),
  top(Theme.marginWidth),
  right(Theme.marginWidth),
]);

let error = style([
  background(red),
  marginBottom(Theme.marginWidth),
  padding(Theme.paddingWidth),
  wordBreak(`breakAll),
]);

let errorTitle = style([
  fontWeight(`bold),
  fontSize(px(18)),
]);

let errorBody = style([
  paddingTop(Theme.paddingWidth),
]);