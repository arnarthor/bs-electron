[@bs.module "electron"] [@bs.scope "app"]
external on:
  (
    [@bs.string] [
      | [@bs.as "ready"] `Ready
      | [@bs.as "closed"] `Closed
      | [@bs.as "window-all-closed"] `WindowAllClosed
      | [@bs.as "activate"] `Activate
    ],
    unit => unit
  ) =>
  unit =
  "";

[@bs.module "electron"] [@bs.scope "app"] external quit: unit => unit = "";

module Dock = {
  [@bs.module "electron"] [@bs.scope ("app", "dock")]
  external hide: unit => unit = "";
};
