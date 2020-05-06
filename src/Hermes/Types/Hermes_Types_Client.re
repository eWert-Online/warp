type t('a) = {
  url: string,
  method: Hermes_Types_Method.t,
  queryString: list((string, string)),
  formData: list((string, string)),
  headers: list((string, string)),
  responseType: 'a,
  onLoad: option(Hermes_Types_ResponseType.t('a) => unit),
};