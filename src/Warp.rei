module Client = Warp_Client;
module Header = Warp_Header;
module Method = Warp_Method;
module QueryString = Warp_QueryString;
module FormData = Warp_FormData;
module ResponseType = Warp_ResponseType;
module Types = Warp_Types;

let onLoad:
  (
    Types.Client.t(Types.ResponseType.payload('a)),
    Types.ResponseType.t('a) => unit
  ) =>
  Types.Client.t(Types.ResponseType.payload('a));

let send:
  Types.Client.t(Types.ResponseType.payload('a)) => option(unit => unit);