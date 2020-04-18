[@react.component]
let make = (~initialState: option(string), ~initialURL: option(string)) => {
  let url = ReasonReactRouter.useUrl();
  let routeConfig: Routes.routeConfig = Routes.getRouteConfig(url);

  <div>
    { React.string("Hello from Reason React") }
    { routeConfig.component }
  </div>
};