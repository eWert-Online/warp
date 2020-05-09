open Warp_Types_Client;

let make = (~url, ~method) => {
  {
    url,
    method,
    queryString: [],
    responseType: Warp_Types_ResponseType.TextResponse(None),
    formData: [],
    headers: [],
    onLoad: None,
    onProgess: None,
    onAbort: None,
  };
};