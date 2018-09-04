module type IpcType = {type rendererToMainMessages;};

module MakeIpcMain = (T: IpcType) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external on:
    ([@bs.as "message"] _, messageCallback(T.rendererToMainMessages)) => unit =
    "";
  [@bs.module "electron"] [@bs.scope "ipcMain"]
  external removeListener:
    ([@bs.as "message"] _, messageCallback(T.rendererToMainMessages)) => unit =
    "";
};
