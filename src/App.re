[@react.component]
let make = (~initialState: option(State.state), ~url: ReasonReactRouter.url) => {
  let page: RoutePage.page = RoutePage.getCorrespondingPage(url);
  let component: option(State.state) => React.element = RouteComponent.getComponentToRender(page);

  <div>
    <Header activeRoute=page />
    { component(initialState) }
  </div>
};