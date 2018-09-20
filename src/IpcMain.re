module type IpcType = {
  type rendererToMainMessages;
  let message: string;
};

module MakeIpcMain = (T: IpcType) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  type ipcCallback = (. event, string) => unit;
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external on: (string, ipcCallback) => unit = "";
  let on = (cb: messageCallback(T.rendererToMainMessages)) =>
    on(T.message, (. event, arg) =>
      cb(. event, arg->Js.Json.parseExn->Json.fromValidJson)
    );
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external removeListener:
    ([@bs.as "message"] _, messageCallback(T.rendererToMainMessages)) => unit =
    "";
};
