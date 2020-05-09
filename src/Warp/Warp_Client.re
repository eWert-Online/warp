open Warp_Types_Client;

let make = (~url, ~method) => {
  {
    url,
    method,
    timeout: 0,
    async: true,
    withCredentials: false,
    queryString: [],
    responseType: Warp_Types_ResponseType.TextResponse(None),
    formData: [],
    headers: [],
    onLoad: None,
    onProgess: None,
    onAbort: None,
  };
};