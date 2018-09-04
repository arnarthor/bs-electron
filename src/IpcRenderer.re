module type IpcRenderer = {
  type mainToRendererMessages;
  type rendererToMainMessages;
};
module MakeIpcRenderer = (T: IpcRenderer) => {
  type event;
  type messageCallback('a) = (. event, 'a) => unit;

  [@bs.send] [@bs.scope "ipcRenderer"]
  external on:
    (
      Window.electronT,
      [@bs.as "message"] _,
      messageCallback(T.mainToRendererMessages)
    ) =>
    unit =
    "";
  let on = on(Window.electron);

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
