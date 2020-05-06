open Hermes_Types_Client;

let make = (~url, ~method) => {
  {
    url,
    method,
    queryString: [],
    onLoad: None,
    formData: [],
    headers: [],
  };
};