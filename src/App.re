[@react.component]
let make = (~initialState: option(State.state), ~url: ReasonReactRouter.url) => {
  let routeConfig: Routes.routeConfig = Routes.getRouteConfig(url);

  <div>
    <Header activeRoute=routeConfig.activeRoute />
    { routeConfig.component(initialState) }
  </div>
};