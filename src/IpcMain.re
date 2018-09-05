module type IpcType = {type rendererToMainMessages;};

module MakeIpcMain = (T: IpcType) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  type ipcCallback = (. event, string) => unit;
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external on: ([@bs.as "message"] _, ipcCallback) => unit = "";
  let on = (cb: messageCallback(T.rendererToMainMessages)) =>
    on((. event, arg) =>
      cb(. event, arg->Js.Json.parseExn->Json.fromValidJson)
    );
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external removeListener:
    ([@bs.as "message"] _, messageCallback(T.rendererToMainMessages)) => unit =
    "";
};
