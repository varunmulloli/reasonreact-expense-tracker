type navLink = {
  id: int,
  name: string,
  page: RoutePage.page,
  active: bool,
};

let navLinks: list(navLink) = [
  {
    id: 0,
    name: "All Posts",
    page: RoutePage.AllPosts,
    active: false,
  },
  {
    id: 1,
    name: "My Posts",
    page: RoutePage.MyPosts,
    active: false,
  },
];

let setActiveNavLink = (id: int) => (navLinkItem: navLink) : navLink => {
  (navLinkItem.id === id) ? { ...navLinkItem, active: true } : navLinkItem;
};

let navLinksWithActiveItem = (id: int) : list(navLink) => Belt.List.map(navLinks, setActiveNavLink(id));

let getNavLinks = (activeRoute: RoutePage.page) : list(navLink) => {
  switch (activeRoute) {
  | RoutePage.AllPosts => navLinksWithActiveItem(0)
  | RoutePage.MyPosts => navLinksWithActiveItem(1)
  | _ => navLinks
  };
};

//TODO: add constants for URLs
let pushRoute = (route: RoutePage.page) => {
  switch route {
  | RoutePage.AllPosts => ReasonReactRouter.push("/")
  | RoutePage.MyPosts => ReasonReactRouter.push("/my-posts")
  | _ => ReasonReactRouter.push("/404")
  };
};

let navLinkComponent = (index: int, navLink: navLink) : React.element => {
  let className = navLink.active ? HeaderCSS.navlinkActive : HeaderCSS.navlink;

  <div key=string_of_int(index) className=className onClick=(_ => pushRoute(navLink.page))>
    <span className=HeaderCSS.navlinkText>{React.string(navLink.name)}</span>
  </div>
};

[@react.component]
let make = (~activeRoute: RoutePage.page) => {
  <div className=HeaderCSS.headerContainer>
    <div className=HeaderCSS.spacer></div>
    { ComponentHelper.renderList(getNavLinks(activeRoute), navLinkComponent) }
  </div>
};