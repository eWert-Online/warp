open Hermes_Types_Client;

let make = (~url, ~method) => {
  {
    url,
    method,
    queryString: [],
    responseType: Hermes_Types_ResponseType.TextResponse(None),
    onLoad: None,
    formData: [],
    headers: [],
  };
};