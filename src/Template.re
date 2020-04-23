let make = (~content, ~initialState, ()) => {j|
  <!DOCTYPE html>
  <html>
    <head>
      <title>Expense Tracker</title>
      <link rel="shortcut icon" type="image/png" href="/dist/favicon.ico">
    </head>
    <body>
      <div id="root">$content</div>
      <script src="/dist/client.js" defer></script>
      <script>
        window.__INITIAL_STATE__ = "$initialState";
      </script>
    </body>
  </html>
|j};