module type IpcType = {
  type mainToRendererMessages;
  type rendererToMainMessages;
};

module MakeIpcRenderer = (T: IpcType) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  [@bs.module "electron"] [@bs.scope "ipcRenderer"]
  external on:
    ([@bs.as "message"] _, messageCallback(T.mainToRendererMessages)) => unit =
    "";
  [@bs.module "electron"] [@bs.scope "ipcRenderer"]
  external removeListener:
    ([@bs.as "message"] _, messageCallback(T.mainToRendererMessages)) => unit =
    "";
  [@bs.module "electron"] [@bs.scope "ipcRenderer"]
  external send: ([@bs.as "message"] _, 'a) => unit = "send";
  let sendWithArg = (arg: T.rendererToMainMessages) =>
    send(arg->Json.toValidJson->Js.Json.stringify);
};

module IpcMain = (T: IpcType) => {
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

  [@bs.module "electron"] [@bs.scope "ipcRenderer"]
  external send: ([@bs.as "message"] _, 'a) => unit = "send";
  let sendWithArg = (arg: T.mainToRendererMessages) =>
    send(arg->Json.toValidJson->Js.Json.stringify);
};