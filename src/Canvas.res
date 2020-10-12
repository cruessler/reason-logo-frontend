type size = {
  width: int,
  height: int,
}

let getViewBox = ({width, height}: size) =>
  [-(width / 2), -(height / 2), width, height] |> Array.map(string_of_int) |> Js.Array.joinWith(" ")

@bs.module("gl-matrix") external vec3: 'a = "vec3"
@bs.module("gl-matrix") external mat4: 'a = "mat4"

let getTurtlePoints = ({x, y, direction}: Vm.turtle) => {
  let point1 = vec3["fromValues"](-15, 0, 0)
  let point2 = vec3["fromValues"](15, 0, 0)
  let point3 = vec3["fromValues"](0, -30, 0)

  let points = [point1, point2, point3]

  let transform = mat4["create"]()

  mat4["fromTranslation"](transform, vec3["fromValues"](x, y, 0))
  mat4["rotate"](transform, transform, direction, vec3["fromValues"](0, 0, 1))
  mat4["translate"](transform, transform, vec3["fromValues"](0, 1, 0))

  points
  |> Array.map(point => vec3["transformMat4"](point, point, transform))
  |> Array.map(([x, y, _z]) => j`$x,$y`)
  |> Js.Array.joinWith(" ")
}

let getRgba = ({red, green, blue, alpha}: Vm.color) => {
  open! Belt.Float

  let red255 = red * 255.0
  let green255 = green * 255.0
  let blue255 = blue * 255.0

  let rgba = j`rgba($red255, $green255, $blue255, $alpha)`

  rgba
}

let getPoints = ({x: x1, y: y1}: Vm.vec2, {x: x2, y: y2}: Vm.vec2) => {
  let points = j`$x1,$y1 $x2,$y2`

  points
}

let renderObject = (object_: Vm.object_) =>
  switch object_ {
  | Line(start, end_, color) =>
    <polyline fill="none" stroke={getRgba(color)} points={getPoints(start, end_)} />
  }

@react.component
let make = (~vm: Vm.vm, ~size: size) =>
  <div id="canvas">
    <svg viewBox={getViewBox(size)}>
      {Array.map(renderObject, vm.environment.objects) |> React.array}
      <polygon id="turtle" points={getTurtlePoints(vm.environment.turtle)} />
    </svg>
  </div>
