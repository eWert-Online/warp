module Client = Hermes_Client;
module Header = Hermes_Header;
module Method = Hermes_Method;
module QueryString = Hermes_QueryString;
module ResponseType = Hermes_ResponseType;
module Types = Hermes_Types;

let onLoad:
  (
    Types.Client.t(Types.ResponseType.payload('a)),
    Types.ResponseType.t('a) => unit
  ) =>
  Types.Client.t(Types.ResponseType.payload('a));

let send:
  Types.Client.t(Types.ResponseType.payload('a)) => option(unit => unit);