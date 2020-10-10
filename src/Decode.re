open! Vm;
open! Json.Decode;

let input = json => {
  Input(json |> field("input", string));
};

let output = json => {
  Output(json |> field("output", string));
};

let error = json => {
  Error(json |> field("error", string));
};

let entry = {
  field("type", string)
  |> andThen(type_ => {
       switch (type_) {
       | "Input" => input
       | "Output" => output
       | "Error" => error
       | _ => failwith({j|invalid entry type: $type_|j})
       }
     });
};

let history = json => {
  json |> array(entry);
};

let turtle = json => {
  {
    x: json |> field("x", float),
    y: json |> field("y", float),
    direction: json |> field("direction", float),
  };
};

let vec2 = json => {
  {x: json |> field("x", float), y: json |> field("y", float)};
};

let color = json => {
  {
    red: json |> field("red", float),
    green: json |> field("green", float),
    blue: json |> field("blue", float),
    alpha: json |> field("alpha", float),
  };
};

let line = json => {
  Line(
    json |> field("start", vec2),
    json |> field("end", vec2),
    json |> field("color", color),
  );
};

let object_ = {
  field("type", string)
  |> andThen(type_ => {
       switch (type_) {
       | "Line" => line
       | _ => failwith({j|invalid object type: $type_|j})
       }
     });
};

let objects = json => {
  json |> array(object_);
};

let environment = json => {
  {
    history:
      json |> field("history", array(entry) |> map(Js.Array.reverseInPlace)),
    objects: json |> field("objects", array(object_)),
    turtle: json |> field("turtle", turtle),
  };
};

let instructions = json => {
  json |> array(string);
};

let binding = json => {
  json |> optional(string);
};

let variables = json => {
  json |> field("variables", dict(binding));
};

let root = json => {
  Root(json |> variables);
};

let local = json => {
  Local(json |> field("address", int), json |> variables);
};

let template = json => {
  Template(
    json |> field("current", optional(string)),
    json |> field("rest", string),
  );
};

let loop = json => {
  Loop(json |> field("current", int));
};

let scope = {
  field("type", string)
  |> andThen(type_ => {
       switch (type_) {
       | "Root" => root
       | "Local" => local
       | "Template" => template
       | "Loop" => loop
       | _ => failwith({j|invalid scope type: $type_|j})
       }
     });
};

let scopes = json => {
  json |> array(scope);
};

let machine = json => {
  {
    instructions: json |> field("instructions", instructions),
    programCounter: json |> field("programCounter", int),
    stack: json |> field("stack", array(string)),
    scopes: json |> field("scopes", scopes),
    environment: json |> field("environment", environment),
  };
};

let fromJson = json => {
  json |> machine;
};
