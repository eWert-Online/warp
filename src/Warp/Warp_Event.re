open Warp_Types_Client;

let onLoad:
  type a.
    (
      Warp_Types_Client.t(Warp_Types_ResponseType.payload(a)),
      Warp_Types_ResponseType.t(a) => unit
    ) =>
    Warp_Types_Client.t(Warp_Types_ResponseType.payload(a)) =
  (client, callback) => {
    let eval: type a. Warp_Types_ResponseType.payload(a) => a =
      fun
      | Warp_Types_ResponseType.ArrayBufferResponse(b) => b
      | Warp_Types_ResponseType.DocumentResponse(d) => d
      | Warp_Types_ResponseType.JSONResponse(j) => j
      | Warp_Types_ResponseType.TextResponse(t) => t;

    {
      ...client,
      onLoad:
        Some(
          data => {
            switch (data) {
            | Warp_Types_ResponseType.Ok(data) => callback(Ok(eval(data)))
            | Warp_Types_ResponseType.Error(message) =>
              callback(Error(message))
            }
          },
        ),
    };
  };

let onProgress = (client, callback) => {
  {...client, onProgess: Some(callback)};
};

let onAbort = (client, callback) => {
  {...client, onAbort: Some(callback)};
};