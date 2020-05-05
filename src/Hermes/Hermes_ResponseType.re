open Hermes_Types_Client;

let setText = client => {
  {
    ...client,
    response: Hermes_Types_ResponseType.TextResponse(None),
    onLoad: _ => (),
  };
};

let setDocument = client => {
  {
    ...client,
    response: Hermes_Types_ResponseType.DocumentResponse(None),
    onLoad: _ => (),
  };
};

let setJson = client => {
  {
    ...client,
    response: Hermes_Types_ResponseType.JSONResponse(None),
    onLoad: _ => (),
  };
};

let setArrayBuffer = client => {
  {
    ...client,
    response: Hermes_Types_ResponseType.ArrayBufferResponse(None),
    onLoad: _ => (),
  };
};