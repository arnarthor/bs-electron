module type IpcRenderer = {
  type mainToRendererMessages;
  type rendererToMainMessages;
};
module MakeIpcRenderer = (T: IpcRenderer) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;
  type ipcCallback = (. event, string) => unit;

  [@bs.send] [@bs.scope "ipcRenderer"]
  external on: (Window.electronT, [@bs.as "message"] _, ipcCallback) => unit =
    "";
  let on = (cb: messageCallback(T.mainToRendererMessages)) =>
    on(Window.electron, (. event, arg) =>
      cb(. event, arg->Js.Json.parseExn->Json.fromValidJson)
    );

  [@bs.send] [@bs.scope "ipcRenderer"]
  external removeListener:
    (
      Window.electronT,
      [@bs.as "message"] _,
      messageCallback(T.mainToRendererMessages)
    ) =>
    unit =
    "";
  let removeListener = removeListener(Window.electron);

  [@bs.send] [@bs.scope "ipcRenderer"]
  external send: (Window.electronT, [@bs.as "message"] _, string) => unit =
    "send";
  let send = (arg: T.rendererToMainMessages) =>
    send(Window.electron, arg->Json.toValidJson->Js.Json.stringify);
};
