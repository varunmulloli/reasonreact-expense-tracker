[@react.component]
let make = (~initialState: option(State.state), ~initialErrors: list(string), ~url: ReasonReactRouter.url) => {
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let component: (option(State.state), list(string)) => React.element = RouteComponent.getComponentToRender(page);

  <div className=AppCss.container>
    <Header activeRoute=page />
    <div className=AppCss.contents>
      { component(initialState, initialErrors) }
    </div>
  </div>
};