let withCredentials:
  (Warp_Types_Client.t('a), bool) => Warp_Types_Client.t('a);

let async: (Warp_Types_Client.t('a), bool) => Warp_Types_Client.t('a);

let timeout: (Warp_Types_Client.t('a), int) => Warp_Types_Client.t('a);