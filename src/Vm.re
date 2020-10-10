type binding = option(string);

type variables = Js.Dict.t(binding);

type scope =
  | Root(variables)
  | Local(int, variables)
  | Template(binding, string)
  | Loop(int);

type entry =
  | Input(string)
  | Output(string)
  | Error(string);

type turtle = {
  x: float,
  y: float,
  direction: float,
};

type vec2 = {
  x: float,
  y: float,
};

type color = {
  red: float,
  green: float,
  blue: float,
  alpha: float,
};

type object_ =
  | Line(vec2, vec2, color);

type environment = {
  history: array(entry),
  objects: array(object_),
  turtle,
};

type vm = {
  environment,
  stack: array(string),
  instructions: array(string),
  scopes: array(scope),
  programCounter: int,
};
