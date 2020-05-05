let make:
  (~url: string, ~method: Hermes_Types_Method.t) =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload(option(string)));