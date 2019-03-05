module Item = {
  type type_ =
    | Label(string)
    | Checkbox(string)
    | Radio(string)
    | Separator;

  type template = {
    .
    "type": string,
    "label": string,
    "enabled": bool,
    "accelerator": option(string),
    "icon": option(string),
    "role": option(string),
    "click": option(unit => unit),
  };
  type t;
  [@bs.module "electron"] [@bs.new] external make: template => t = "MenuItem";
  let make =
      (type_, ~enabled=true, ~icon=?, ~accelerator=?, ~role=?, ~click=?, ()) => {
    let (label, type_) =
      switch (type_) {
      | Label(s) => (s, "normal")
      | Checkbox(s) => (s, "checkbox")
      | Radio(s) => (s, "radio")
      | Separator => ("", "separator")
      };
    make({
      "type": type_,
      "label": label,
      "accelerator": accelerator,
      "icon": icon,
      "role": role,
      "enabled": enabled,
      "click": click,
    });
  };
};
type t;
[@bs.module "electron"] [@bs.new] external make: unit => t = "Menu";
[@bs.send] external append: (t, Item.t) => unit = "";