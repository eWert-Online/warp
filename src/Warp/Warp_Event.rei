let onLoad:
  (
    Warp_Types_Client.t(Warp_Types_ResponseType.payload('a)),
    Warp_Types_ResponseType.t('a) => unit
  ) =>
  Warp_Types_Client.t(Warp_Types_ResponseType.payload('a));

let onProgress:
  (Warp_Types_Client.t('a), Dom.progressEvent => unit) =>
  Warp_Types_Client.t('a);

let onAbort:
  (Warp_Types_Client.t('a), unit => unit) => Warp_Types_Client.t('a);