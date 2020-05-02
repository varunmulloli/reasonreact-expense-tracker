open Css;

let headerContainer = merge([
  Theme.border,
  style([
    display(`flex),
    height(px(32)),
  ]),
]);

let spacer = Theme.spacer;

let navlink = style([
  fontWeight(`bold),
  textAlign(`center),
  marginTop(`auto),
  marginRight(Theme.marginWidth),
  marginBottom(`auto),
  marginLeft(Theme.marginWidth),
]);

let navlinkActive = merge([
  navlink,
  style([
    textDecoration(`underline),
  ]),
]);

let navlinkText = style([
  cursor(`pointer),
  hover([
    textDecoration(`underline),
  ]),
]);
