type t;

type windowConfig = {
  .
  width: int,
  height: int,
  frame: Js.null(bool),
  titleBarStyle: Js.null(string),
  fullscreenable: Js.null(bool),
  resizeable: Js.null(bool),
};

[@bs.obj]
external makeWindowConfig:
  (
    ~width: int,
    ~height: int,
    ~frame: bool=?,
    ~titleBarStyle: [@bs.string] [ | [@bs.as "hidden"] `Hidden]=?,
    ~fullscreenable: bool=?,
    ~resizeable: bool=?,
    unit
  ) =>
  windowConfig =
  "";

[@bs.module "electron"] [@bs.new]
external make: windowConfig => t = "BrowserWindow";

[@bs.send] external loadURL: (t, string) => unit = "";

[@bs.send]
external on:
  (
    t,
    [@bs.string] [ | [@bs.as "closed"] `Closed | [@bs.as "blur"] `Blur],
    unit => unit
  ) =>
  unit =
  "";

[@bs.send] external openDevTools: t => unit = "";

[@bs.send] external isVisible: t => bool = "";

[@bs.send] external show: t => unit = "";
[@bs.send] external hide: t => unit = "";
[@bs.send] external focus: t => unit = "";

[@bs.send]
external setPosition: (t, ~x: int, ~y: int, ~animate: bool) => unit = "";

type visibility = [ | `Showing | `Hidden];
let getVisibility = t => isVisible(t) ? `Showing : `Hidden;
