type t;

[@bs.module "electron"] [@bs.new] external make: string => t = "Tray";

type trayEvent;
[@bs.send]
external on:
  (
    t,
    [@bs.string] [ | [@bs.as "click"] `Click],
    (trayEvent, Common.abs_bounds) => unit
  ) =>
  unit =
  "";

let getBounds = t => Common.boundsFromJs(Common.getBoundsJs(t));

[@bs.send] external setContextMenu: (t, Menu.t) => unit = "";
