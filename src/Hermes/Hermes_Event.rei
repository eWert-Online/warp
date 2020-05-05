let onLoad:
  (
    Hermes_Types_Client.t(Hermes_Types_ResponseType.payload('a)),
    Hermes_Types_ResponseType.t('a) => unit
  ) =>
  Hermes_Types_Client.t(Hermes_Types_ResponseType.payload('a));