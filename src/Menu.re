module Item = {
  type t;
  type type_ =
    | Label(string)
    | Checkbox(string)
    | Radio(string)
    | Submenu(string, array(t))
    | Separator

  and template = {
    .
    "type": string,
    "label": string,
    "enabled": bool,
    "submenu": array(t),
    "sublabel": option(string),
    "accelerator": option(string),
    "icon": option(string),
    "role": option(string),
    "click": option(unit => unit),
  };
  [@bs.module "electron"] [@bs.new] external make: template => t = "MenuItem";
  let make =
      (
        type_,
        ~sublabel=?,
        ~enabled=true,
        ~icon=?,
        ~accelerator=?,
        ~role=?,
        ~click=?,
        (),
      ) => {
    let (label, type_, submenu) =
      switch (type_) {
      | Label(s) => (s, "normal", [||])
      | Checkbox(s) => (s, "checkbox", [||])
      | Radio(s) => (s, "radio", [||])
      | Separator => ("", "separator", [||])
      | Submenu(s, l) => (s, "submenu", l)
      };
    make({
      "type": type_,
      "label": label,
      "sublabel": sublabel,
      "submenu": submenu,
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