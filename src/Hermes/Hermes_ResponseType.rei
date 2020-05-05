let setText:
  Hermes_Types_Client.t('a) =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let setDocument:
  Hermes_Types_Client.t('a) =>
  Hermes_Types_Client.t(
    Hermes_Types_ResponseType.payload(option(Dom.document)),
  );

let setJson:
  Hermes_Types_Client.t('a) =>
  Hermes_Types_Client.t(
    Hermes_Types_ResponseType.payload(option(Js.Json.t)),
  );

let setArrayBuffer:
  Hermes_Types_Client.t('a) =>
  Hermes_Types_Client.t(
    Hermes_Types_ResponseType.payload(option(Js.Typed_array.ArrayBuffer.t)),
  );