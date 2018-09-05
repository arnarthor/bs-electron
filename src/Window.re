type t;
[@bs.val] external window: t = "";
module MakeWindowRequire = (T: {
                              type moduleT;
                              let moduleName: string;
                            }) => {
  [@bs.send] external require: (t, string) => T.moduleT = "";
  let make = () => require(window, T.moduleName);
};

type electronT;
module Electron =
  MakeWindowRequire({
    type moduleT = electronT;
    let moduleName = "electron";
  });
let electron = Electron.make();
