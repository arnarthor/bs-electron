type t;

[@bs.module "electron"] [@bs.new] external make: string => t = "Tray";

type trayBounds;
type trayEvent;
[@bs.send]
external on:
  (
    t,
    [@bs.string] [ | [@bs.as "click"] `Click],
    (trayEvent, trayBounds) => unit
  ) =>
  unit =
  "";
