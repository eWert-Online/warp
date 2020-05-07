open Warp_Types_Client;

let setText = client => {
  {
    ...client,
    responseType: Warp_Types_ResponseType.TextResponse(None),
    onLoad: None,
  };
};

let setDocument = client => {
  {
    ...client,
    responseType: Warp_Types_ResponseType.DocumentResponse(None),
    onLoad: None,
  };
};

let setJson = client => {
  {
    ...client,
    responseType: Warp_Types_ResponseType.JSONResponse(None),
    onLoad: None,
  };
};

let setArrayBuffer = client => {
  {
    ...client,
    responseType: Warp_Types_ResponseType.ArrayBufferResponse(None),
    onLoad: None,
  };
};