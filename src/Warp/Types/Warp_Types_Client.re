type t('a) = {
  url: string,
  method: Warp_Types_Method.t,
  queryString: list((string, string)),
  formData: list((string, string)),
  headers: list((string, string)),
  responseType: 'a,
  onLoad: option(Warp_Types_ResponseType.t('a) => unit),
};