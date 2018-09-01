type t;

[@bs.deriving {jsConverter: newType}]
type windowConfig = {
  width: int,
  height: int,
  frame: bool,
  titleBarStyle: string,
};

[@bs.module "electron"] [@bs.new]
external make: abs_windowConfig => t = "BrowserWindow";

let make = options => make(windowConfigToJs(options));

[@bs.send] external loadURL: (t, string) => unit = "";

[@bs.send]
external on:
  (t, [@bs.string] [ | [@bs.as "closed"] `Closed], unit => unit) => unit =
  "";

[@bs.send] external openDevTools: t => unit = "";
