// This file is almost identical to the one provided by `bsb -init …`. It was
// slightly refactored and stripped of most of its comments.

var websocketReloader;
var LAST_SUCCESS_BUILD_STAMP =
  localStorage.getItem("LAST_SUCCESS_BUILD_STAMP") || 0;
// The port can be set via the `-ws` flag provided to `bsb`.
var webSocketPort = 9999;

function setUpWebSocket() {
  if (websocketReloader == null || websocketReloader.readyState !== 1) {
    try {
      websocketReloader = new WebSocket(
        `ws://${window.location.hostname}:${webSocketPort}`
      );

      websocketReloader.onmessage = (message) => {
        var newTimestamp = JSON.parse(message.data).LAST_SUCCESS_BUILD_STAMP;

        if (newTimestamp > LAST_SUCCESS_BUILD_STAMP) {
          LAST_SUCCESS_BUILD_STAMP = newTimestamp;
          localStorage.setItem(
            "LAST_SUCCESS_BUILD_STAMP",
            LAST_SUCCESS_BUILD_STAMP
          );

          location.reload(true);
        }
      };
    } catch (exception) {
      console.error(
        "The watcher tried to connect to web socket, but failed. Here’s the message:"
      );
      console.error(exception);
    }
  }
}

setUpWebSocket();
setInterval(setUpWebSocket, 2000);
