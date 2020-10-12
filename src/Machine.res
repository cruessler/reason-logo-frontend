let renderBinding = ((name, binding)) =>
  <tr>
    <td> {name |> React.string} </td>
    <td> {binding |> Js.Option.getWithDefault("_") |> React.string} </td>
  </tr>

let renderVariables = (variables: Vm.variables) =>
  <table>
    <tbody> {Js.Dict.entries(variables) |> Array.map(renderBinding) |> React.array} </tbody>
  </table>

let renderRootScope = variables =>
  <li> <h3> {React.string("Root")} </h3> {renderVariables(variables)} </li>

let renderLocalScope = (address, variables) =>
  <li>
    <h3> {React.string("Local@" ++ string_of_int(address))} </h3> {renderVariables(variables)}
  </li>

let renderTemplateScope = (current, rest) =>
  <li>
    <h3> {React.string("Template")} </h3>
    <table>
      <tbody>
        <tr>
          <td> {React.string("current")} </td>
          <td> {React.string(current |> Js.Option.getWithDefault("_"))} </td>
        </tr>
        <tr> <td> {React.string(rest)} </td> <td> {React.string(rest)} </td> </tr>
      </tbody>
    </table>
  </li>

let renderLoopScope = current =>
  <li> <h3> {React.string("Loop@" ++ string_of_int(current))} </h3> </li>

let renderScope = scope =>
  switch scope {
  | Vm.Root(variables) => renderRootScope(variables)
  | Local(address, variables) => renderLocalScope(address, variables)
  | Template(current, rest) => renderTemplateScope(current, rest)
  | Loop(current) => renderLoopScope(current)
  }

let renderStack = stack =>
  <div id="stack">
    <h2> {React.string("Stack")} </h2>
    <ul> {Array.map(entry => <li> {React.string(entry)} </li>, stack) |> React.array} </ul>
  </div>

let renderScopes = scopes =>
  <div id="scopes">
    <h2> {React.string("Scopes")} </h2> <ul> {Array.map(renderScope, scopes) |> React.array} </ul>
  </div>

let renderInstructions = (instructions, programCounter) => {
  let currentInstruction =
    Belt.Array.get(instructions, programCounter) |> Js.Option.getWithDefault("none")

  <div id="instructions">
    <h2> {React.string("Instructions")} </h2>
    <h3> {React.string("Next")} </h3>
    <table>
      <tbody>
        <tr className="current">
          <td> {programCounter |> string_of_int |> React.string} </td>
          <td> {currentInstruction |> React.string} </td>
        </tr>
      </tbody>
    </table>
    <table id="program"> <tbody> {Array.mapi((i, instruction) =>
          if i === programCounter {
            <tr className="current">
              <td> {i |> string_of_int |> React.string} </td>
              <td> {instruction |> React.string} </td>
            </tr>
          } else {
            <tr>
              <td> {i |> string_of_int |> React.string} </td>
              <td> {instruction |> React.string} </td>
            </tr>
          }
        , instructions) |> React.array} </tbody> </table>
  </div>
}

@react.component
let make = (~vm: Vm.vm) =>
  <div id="machine">
    {renderStack(vm.stack)}
    {renderScopes(vm.scopes)}
    {renderInstructions(vm.instructions, vm.programCounter)}
  </div>
