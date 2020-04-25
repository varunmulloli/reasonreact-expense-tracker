open Css;

let headerContainer = style([
  display(`flex),
  width(px(600)),
  height(px(32)),
  marginLeft(`auto),
  marginRight(`auto),
  paddingLeft(px(16)),
  paddingRight(px(16)),
  border(px(1),`solid,hex("000")),
]);

let navlink = style([
  width(pct(100.)),
  margin(`auto),
  fontWeight(`bold),
  textAlign(`center),
]);

let navlinkActive = style([
  textDecoration(`underline),
]);

let navlinkText = style([
  cursor(`pointer),
]);
