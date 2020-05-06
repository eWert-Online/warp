let options:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let get:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let head:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let post:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let put:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let delete:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let trace:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));

let connect:
  string =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));