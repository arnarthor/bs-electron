type t;
[@bs.val] external window: t = "";
module MakeWindowRequire = (T: {type moduleT;}) => {
  [@bs.send] external require: (t, string) => T.moduleT = "";
  let require = require(window);
};

type electronT;
module Electron =
  MakeWindowRequire({
    type moduleT = electronT;
  });
let electron = Electron.require("electron");
