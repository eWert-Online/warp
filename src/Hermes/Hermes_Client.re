open Hermes_Types_Client;

let make = (~url, ~method) => {
  {
    url,
    method,
    queryString: [],
    response: Hermes_Types_ResponseType.TextResponse(None),
    onLoad: _response => (),
    formData: [],
    headers: [],
  };
};