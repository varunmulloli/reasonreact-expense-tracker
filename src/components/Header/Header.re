[@react.component]
let make = (~activeRoute: RoutePage.page) => {
  let activeNavLink = Css.merge([HeaderCSS.navlink, HeaderCSS.navlinkActive]);
  //TODO: Change this shit
  let navLinkClass = (page: RoutePage.page) => {
    (activeRoute === page) ? activeNavLink : HeaderCSS.navlink;
  };
  let pushRoute = (route: RoutePage.page) => {
    switch route {
    | RoutePage.AllPosts => ReasonReactRouter.push("/")
    | RoutePage.MyPosts => ReasonReactRouter.push("/my-posts")
    | _ => ReasonReactRouter.push("/404")
    };
  };

  <div className=HeaderCSS.headerContainer>
    <div className=navLinkClass(RoutePage.AllPosts) onClick=(_ => pushRoute(RoutePage.AllPosts))>
      <span className=HeaderCSS.navlinkText>{React.string("All Posts")}</span>
    </div>

    <div className=navLinkClass(RoutePage.MyPosts) onClick=(_ => pushRoute(RoutePage.MyPosts))>
      <span className=HeaderCSS.navlinkText>{React.string("My Posts")}</span>
    </div>
  </div>
};