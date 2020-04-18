let make = (~content, ~initialState, ~initialURL, ()) => {j|
  <!DOCTYPE html>
  <html>
    <head>
      <title>Expense Tracker</title>
    </head>
    <body>
      <div id="root">$content</div>
      <script src="/dist/client.js" defer></script>
      <script>
        window.__INITIAL_STATE__ = $initialState;
        window.__INITIAL_URL__ = $initialURL;
      </script>
    </body>
  </html>
|j};