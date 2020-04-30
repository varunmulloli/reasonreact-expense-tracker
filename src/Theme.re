open Css;

let marginWidth = px(16);
let paddingWidth = px(8);

let highlightColor = hex("f5f5f5");

let border = style([
  border(px(1), `solid, black),
]);

let spacer = style([
  flexGrow(1.0),
]);

global("body", [
  margin(px(0)),
]);