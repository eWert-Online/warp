open Hermes_Types_Method;

let options = (url: string) => {
  Hermes_Client.make(~url, ~method=OPTIONS);
};

let get = (url: string) => {
  Hermes_Client.make(~url, ~method=GET);
};

let head = (url: string) => {
  Hermes_Client.make(~url, ~method=HEAD);
};

let post = (url: string) => {
  Hermes_Client.make(~url, ~method=POST);
};

let put = (url: string) => {
  Hermes_Client.make(~url, ~method=PUT);
};

let delete = (url: string) => {
  Hermes_Client.make(~url, ~method=DELETE);
};

let trace = (url: string) => {
  Hermes_Client.make(~url, ~method=TRACE);
};

let connect = (url: string) => {
  Hermes_Client.make(~url, ~method=CONNECT);
};