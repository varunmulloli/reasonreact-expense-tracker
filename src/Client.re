let initialState: option(string) = [%bs.raw {|window.__INITIAL_STATE__|} ];
let initialURL: option(string) = [%bs.raw {|window.__INITIAL_URL__|} ];

ReactDOMRe.hydrateToElementWithId(<App initialState=initialState initialURL=initialURL />, "root");