let make = (~content, ()) => {j|
  <!DOCTYPE html>
  <html>
    <head>
      <title>Expense Tracker</title>
    </head>
    <body>
      <div id="root">$content</div>
      <script src="/dist/client.js" defer></script>
    </body>
  </html>
|j};