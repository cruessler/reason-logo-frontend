let style = {j|
  html {
    --primary-color: rgb(248, 248, 242);
    --primary-background-color: rgb(37, 36, 36);
    --monospace-font: 12px "Fira Code", monospace;
  }

  * {
    box-sizing: border-box;
  }

  body {
    width: 100vw;
    height: 100vh;
    margin: 0;
    padding: 0;
  }

  button {
    color: var(--primary-background-color);
    background-color: #cfcfcf;
    border-radius: 5px;
    border-style: none;
    padding: 5px 20px;
    cursor: pointer;
    transition: background-color 0.2s ease-in;
  }
  button:hover {
    background-color: #efefef;
    transition: background-color 0.2s ease-in;
  }

  #app {
    width: 100%;
    height: 100%;
    position: relative;
    font-family: "Raleway", -apple-system, system, sans-serif;
  }

  #overlay {
    position: absolute;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    display: grid;
    grid-template-columns: 4fr 9fr 3fr;
    grid-template-areas: "overlay-left . vm";
  }

  #overlay-left {
    grid-area: overlay-left;
    display: grid;
    grid-template-rows: 5fr auto;
    grid-template-areas: "terminal" "examples";
    overflow-y: auto;
    box-shadow: 5px 5px 5px 0 rgb(201, 199, 199);
  }

  #terminal {
    grid-area: terminal;
    display: grid;
    grid-template-rows: 1fr auto;
    grid-template-areas: "history" "controls";
    overflow-y: auto;
    color: var(--primary-color);
    background-color: var(--primary-background-color);
  }

  #history {
    display: grid;
    grid-template-rows: 5fr 1fr;
    grid-template-areas: "entries" "prompt";
    overflow-y: auto;
  }

  #entries {
    grid-area: entries;
    margin: 0;
    padding: 0;
    font: var(--monospace-font);
    overflow-y: auto;
  }

  #prompt {
    grid-area: prompt;
    width: 100%;
    font: var(--monospace-font);
    background-color: #312f2f;
    border-style: none;
    color: #eaeaf0;
  }

  #controls {
    grid-area: controls;
    padding: 10px;
    display: flex;
  }

  #controls > button:first-child {
    margin-left: auto;
  }
  #controls > button {
    margin-left: 10px;
  }

  #entries > li {
    white-space: pre-wrap;
  }
  #entries > li.input {
    color: rgba(247, 248, 242, 0.7);
  }
  #entries > li.input:before {
    content: "> ";
  }
  #entries > li.error {
    color: rgb(248, 80, 80);
  }
  #entries > li.error:before {
    content: "! ";
  }

  #examples {
    grid-area: examples;
    padding: 1em;
    overflow-y: auto;
    color: var(--primary-color);
    background-color: var(--primary-background-color);
  }

  #examples h1 {
    margin: 0;
  }

  #examples ul {
    display: flex;
    flex-wrap: wrap;
    column-gap: 5px;
    padding: 0;
    list-style: none;
  }

  #examples li {
    padding: 0.2em 0;
  }

  #examples button {
    font-size: smaller;
  }

  #machine h2 {
    margin: 0;
  }

  #machine ul {
    font: var(--monospace-font);
    padding: 0;
    list-style: none;
  }

  #machine li {
    padding: 0.2em 0;
  }

  #machine table {
    font: var(--monospace-font);
  }

  #machine tr.current {
    color: rgb(18, 18, 18);
    background-color: var(--primary-color);
  }

  #machine {
    grid-area: vm;
    padding: 1em;
    overflow-y: auto;
    color: var(--primary-color);
    background-color: var(--primary-background-color);
    box-shadow: -5px 5px 5px 0 rgb(201, 199, 199);
  }

  #program {
    overflow-y: auto;
  }

  #canvas {
    width: 100%;
    height: 100%;
  }

  #turtle {
    fill: none;
    stroke: black;
  }
|j};
