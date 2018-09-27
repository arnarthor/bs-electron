module type IpcRenderer = {
  type mainToRendererMessages;
  type rendererToMainMessages;
  let message: string;
};
module MakeIpcRenderer = (T: IpcRenderer) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  type ipcCallback = (. event, string) => unit;

  [@bs.send] [@bs.scope "ipcRenderer"]
  external on: (Window.electronT, string, ipcCallback) => unit = "";
  let on = (cb: messageCallback(T.mainToRendererMessages)) =>
    on(Window.electron, T.message, (. event, arg) =>
      cb(. event, arg->Js.Json.parseExn->Json.fromValidJson)
    );

  [@bs.send] [@bs.scope "ipcRenderer"]
  external removeListener:
    (Window.electronT, string, messageCallback(T.mainToRendererMessages)) =>
    unit =
    "";
  let removeListener = removeListener(Window.electron, T.message);

  [@bs.send] [@bs.scope "ipcRenderer"]
  external send: (Window.electronT, string, string) => unit = "send";
  let send = (arg: T.rendererToMainMessages) =>
    send(
      Window.electron,
      T.message,
      arg->Json.toValidJson->Js.Json.stringify,
    );
};
