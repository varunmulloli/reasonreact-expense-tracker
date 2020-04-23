[@react.component]
let make = (~initialState: State.state) => {
  let url = ReasonReactRouter.useUrl();
  let routeConfig: Routes.routeConfig = Routes.getRouteConfig(url);
  <div>
    { routeConfig.component(initialState) }
  </div>
};