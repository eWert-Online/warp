module Client = Hermes_Client;
module Event = Hermes_Event;
module Header = Hermes_Header;
module Method = Hermes_Method;
module QueryString = Hermes_QueryString;
module ResponseType = Hermes_ResponseType;
module Types = Hermes_Types;

let send:
  Types.Client.t(Types.ResponseType.payload('a)) => option(unit => unit);