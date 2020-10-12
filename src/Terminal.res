let renderEntry = (entry: Vm.entry) =>
  switch entry {
  | Input(input) => <li className="input"> {React.string(input)} </li>
  | Output(output) => <li className="output"> {React.string(output)} </li>
  | Error(error) => <li className="error"> {React.string(error)} </li>
  }

let renderHistory = history => history |> Js.Array.map(renderEntry) |> React.array

@react.component
let make = (~prompt, ~setPrompt, ~vm: Vm.vm, ~onCompile, ~onStep, ~onContinue) =>
  <div id="terminal">
    <div id="history">
      <ul id="entries"> {renderHistory(vm.environment.history)} </ul>
      <textarea
        id="prompt"
        value=prompt
        onChange={event => {
          let value: string = ReactEvent.Form.target(event)["value"]
          setPrompt(_ => value)
        }}
      />
    </div>
    <div id="controls">
      <button onClick=onCompile> {React.string("Compile")} </button>
      <button onClick=onStep> {React.string("Step")} </button>
      <button onClick=onContinue> {React.string("Continue")} </button>
    </div>
  </div>
