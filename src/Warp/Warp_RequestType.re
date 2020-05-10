open Warp_Types_Client;

let setForm = client => {
  {...client, requestType: "application/x-www-form-urlencoded"};
};

let setJson = client => {
  {...client, requestType: "application/json"};
};