open Hermes_Types_Client;

let onLoad:
  type a.
    (
      t(Hermes_Types_ResponseType.payload(a)),
      Hermes_Types_ResponseType.t(a) => unit
    ) =>
    t(Hermes_Types_ResponseType.payload(a)) =
  (client, callback) => {
    let eval: type a. Hermes_Types_ResponseType.payload(a) => a =
      fun
      | Hermes_Types_ResponseType.ArrayBufferResponse(b) => b
      | Hermes_Types_ResponseType.DocumentResponse(d) => d
      | Hermes_Types_ResponseType.JSONResponse(j) => j
      | Hermes_Types_ResponseType.TextResponse(t) => t;

    {
      ...client,
      onLoad: data => {
        switch (data) {
        | Hermes_Types_ResponseType.Ok(data) => callback(Ok(eval(data)))
        | Hermes_Types_ResponseType.Error(message) =>
          callback(Error(message))
        };
      },
    };
  };