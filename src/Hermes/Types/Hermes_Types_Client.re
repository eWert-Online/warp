type t('a) = {
  url: string,
  method: Hermes_Types_Method.t,
  queryString: list((string, string)),
  formData: list((string, string)),
  headers: list((string, string)),
  response: 'a,
  onLoad: Hermes_Types_ResponseType.t('a) => unit,
};