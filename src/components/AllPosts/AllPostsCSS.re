open Css;

let postContainer = style([
  marginTop(Theme.marginWidth),
  hover([
    background(Theme.highlightColor),
    cursor(`pointer),
  ]),
]);