// This is an external dependency that is, as of October 2020, not part of
// reason-logo-frontend.
//
// It can be copied from the build output of [elm-logo].
//
// [elm-logo]: https://github.com/cruessler/elm-logo

let worker = [%bs.raw {|new Worker("/worker.js")|}];

let initialVm: Vm.vm = {
  stack: [||],
  instructions: [||],
  scopes: [||],
  environment: {
    history: [||],
    objects: [||],
    turtle: {
      x: 0.,
      y: 0.,
      direction: 0.,
    },
  },
  programCounter: 0,
};

[@bs.val] external window: Js.t({..}) = "window";

[@react.component]
let make = () => {
  let (prompt, setPrompt) = React.useState(() => "");
  let (vm, setVm) = React.useState(() => initialVm);

  let (size, setSize) =
    React.useState(() => {
      let value: Canvas.size = {
        width: window##innerWidth,
        height: window##innerHeight,
      };

      value;
    });

  let onMessage = event => {
    let vm = event##data |> Decode.fromJson;

    setVm(_ => vm);
  };

  React.useEffect0(() => {
    worker##addEventListener("message", onMessage);

    Some(_ => worker##removeEventListener("message", onMessage));
  });

  let onResize = () => {
    setSize(_ => {width: window##innerWidth, height: window##innerHeight});
  };

  React.useEffect0(() => {
    window##addEventListener("resize", onResize);

    Some(_ => window##removeEventListener("resize", onResize));
  });

  let onCompile = _ => {
    worker##postMessage({"type": "Compile", "source": prompt});
  };

  let onStep = _ => {
    worker##postMessage({"type": "Step"});
  };

  let onContinue = _ => {
    worker##postMessage({"type": "Continue"});
  };

  <main id="app">
    <Canvas vm size />
    <div id="overlay">
      <div id="overlay-left">
        <Terminal prompt setPrompt vm onCompile onStep onContinue />
        <Examples setPrompt />
      </div>
      <Machine vm />
    </div>
  </main>;
};
