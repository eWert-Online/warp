let add:
  (Hermes_Types_Client.t('a), string, string) => Hermes_Types_Client.t('a);

let set:
  (Hermes_Types_Client.t('a), list((string, string))) =>
  Hermes_Types_Client.t('a);

let remove: (Hermes_Types_Client.t('a), string) => Hermes_Types_Client.t('a);