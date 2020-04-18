type routeConfig = {
  component: React.element,
  loadData: option(unit => Js.Promise.t(option(Js.Json.t))),
};

let loadAllPostsData = () => PostsAPI.fetchAllPosts();

let getRouteConfig = (url: ReasonReactRouter.url) : routeConfig =>  switch url.path {
  | [] => { component: <AllPosts />, loadData: Some(loadAllPostsData) }
  | _ => { component: <AllPosts />, loadData: None }
};