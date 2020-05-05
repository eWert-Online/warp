open Hermes_Types_Method;

let get = (url: string) => {
  Hermes_Client.make(~url, ~method=GET);
};

let post = (url: string) => {
  Hermes_Client.make(~url, ~method=POST);
};

let put = (url: string) => {
  Hermes_Client.make(~url, ~method=PUT);
};

let patch = (url: string) => {
  Hermes_Client.make(~url, ~method=PATCH);
};

let delete = (url: string) => {
  Hermes_Client.make(~url, ~method=DELETE);
};

let head = (url: string) => {
  Hermes_Client.make(~url, ~method=HEAD);
};

let options = (url: string) => {
  Hermes_Client.make(~url, ~method=OPTIONS);
};