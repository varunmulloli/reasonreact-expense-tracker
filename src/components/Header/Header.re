[@react.component]
let make = (~activeRoute: Types.ActiveRoute.activeRoute) => {
  let activeNavLink = Css.merge([HeaderCSS.navlink, HeaderCSS.navlinkActive]);
  let navLinkClass = (route: Types.ActiveRoute.activeRoute) => {
    (activeRoute === route) ? activeNavLink : HeaderCSS.navlink;
  };
  let pushRoute = (route: Types.ActiveRoute.activeRoute) => {
    switch route {
    | Types.ActiveRoute.AllPosts => ReasonReactRouter.push("/")
    | Types.ActiveRoute.MyPosts => ReasonReactRouter.push("/my-posts")
    | _ => ReasonReactRouter.push("/404")
    };
  };

  <div className=HeaderCSS.headerContainer>
    <div className=navLinkClass(Types.ActiveRoute.AllPosts) onClick=(_ => pushRoute(Types.ActiveRoute.AllPosts))>
      <span className=HeaderCSS.navlinkText>{React.string("All Posts")}</span>
    </div>

    <div className=navLinkClass(Types.ActiveRoute.MyPosts) onClick=(_ => pushRoute(Types.ActiveRoute.MyPosts))>
      <span className=HeaderCSS.navlinkText>{React.string("My Posts")}</span>
    </div>
  </div>
};