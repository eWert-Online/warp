type method =
  | GET
  | POST
  | PUT
  | PATCH
  | DELETE
  | HEAD
  | OPTIONS;

type responseType('a) =
  | ArrayBufferResponse(option(Js.Typed_array.array_buffer))
    : responseType(option(Js.Typed_array.array_buffer))
  | DocumentResponse(option(Dom.document))
    : responseType(option(Dom.document))
  | JSONResponse(option(Js.Json.t)): responseType(option(Js.Json.t))
  | TextResponse(option(string)): responseType(option(string));

type response('a) =
  | Error(string)
  | Ok('a);

type t('a) = {
  url: string,
  method,
  queryString: list((string, string)),
  formData: list((string, string)),
  headers: list((string, string)),
  response: 'a,
};

let make = (~url, ~method) => {
  {
    url,
    method,
    queryString: [],
    response: TextResponse(None),
    formData: [],
    headers: [],
  };
};

/* ================= METHODS =============== */
let get = (url: string) => {
  make(~url, ~method=GET);
};

let post = (url: string) => {
  make(~url, ~method=POST);
};

let put = (url: string) => {
  make(~url, ~method=PUT);
};

let patch = (url: string) => {
  make(~url, ~method=PATCH);
};

let delete = (url: string) => {
  make(~url, ~method=DELETE);
};

let head = (url: string) => {
  make(~url, ~method=HEAD);
};

let options = (url: string) => {
  make(~url, ~method=OPTIONS);
};

/* ================= HEADERS =============== */
let addHeader = (client, header) => {
  {...client, headers: [header, ...client.headers]};
};

let setHeaders = (client, headers) => {
  {...client, headers};
};

let removeHeader = (client, headerToRemove) => {
  {
    ...client,
    headers:
      Belt.List.keep(
        client.headers,
        header => {
          let (key, _value) = header;
          key !== headerToRemove;
        },
      ),
  };
};

/* ================= DATA =============== */
let addQueryString = (client, queryString) => {
  {...client, queryString: [queryString, ...client.queryString]};
};

let setQueryString = (client, queryString) => {
  {...client, queryString};
};

let removeQueryString = (client, keyToRemove) => {
  {
    ...client,
    headers:
      Belt.List.keep(
        client.headers,
        header => {
          let (key, _value) = header;
          key !== keyToRemove;
        },
      ),
  };
};

/* ================= RESPONSE TYPES =============== */
let setResponseTypeText = client => {
  {...client, response: TextResponse(None)};
};

let setResponseTypeDocument = client => {
  {...client, response: DocumentResponse(None)};
};

let setResponseTypeJSON = client => {
  {...client, response: JSONResponse(None)};
};

let setResponseTypeArrayBuffer = client => {
  {...client, response: ArrayBufferResponse(None)};
};

/* ================= FINISHERS =============== */
let send:
  type a. (t(responseType(a)), response(a) => unit) => option(unit => unit) =
  (client, callback) => {
    let eval: type a. responseType(a) => a =
      fun
      | ArrayBufferResponse(b) => b
      | DocumentResponse(d) => d
      | JSONResponse(j) => j
      | TextResponse(t) => t;

    let xhr = Hermes_XHR.make();

    let url =
      if (Belt.List.length(client.queryString) > 0) {
        let hd = Belt.List.head(client.queryString);
        let tl = Belt.List.tail(client.queryString);
        switch (hd, tl) {
        | (Some((fst_key, fst_val)), Some(tl)) =>
          client.url
          ++ "?"
          ++ fst_key
          ++ "="
          ++ fst_val
          ++ Belt.List.reduce(tl, "", (acc, (key, value)) =>
               acc ++ "&" ++ key ++ "=" ++ value
             )
        | (Some((fst_key, fst_val)), None) =>
          client.url ++ "?" ++ fst_key ++ "=" ++ fst_val
        | _ => client.url
        };
      } else {
        client.url;
      };

    xhr->Hermes_XHR.open_(
      ~url,
      ~method=
        switch (client.method) {
        | POST => "Post"
        | GET => "Get"
        | PUT => "Put"
        | PATCH => "Patch"
        | DELETE => "Delete"
        | HEAD => "Head"
        | OPTIONS => "Options"
        },
      (),
    );

    Belt.List.forEach(client.headers, ((key, value)) => {
      xhr->Hermes_XHR.setRequestHeader(key, value)
    });

    xhr->Hermes_XHR.addEventListener(
      `error(_ => {callback(Error(xhr->Hermes_XHR.statusText))}),
    );
    xhr->Hermes_XHR.addEventListener(
      `timeout(_ => {callback(Error(xhr->Hermes_XHR.statusText))}),
    );

    xhr->Hermes_XHR.addEventListener(
      `load(
        _ => {
          switch (client.response) {
          | TextResponse(_) =>
            callback(
              Ok(
                eval(
                  TextResponse(
                    xhr->Hermes_XHR.responseText->Js.Nullable.toOption,
                  ),
                ),
              ),
            )
          | JSONResponse(_) =>
            callback(
              Ok(
                eval(
                  JSONResponse(
                    xhr->Hermes_XHR.responseJson->Js.Nullable.toOption,
                  ),
                ),
              ),
            )
          | DocumentResponse(_) =>
            callback(
              Ok(
                eval(
                  DocumentResponse(
                    xhr->Hermes_XHR.responseDocument->Js.Nullable.toOption,
                  ),
                ),
              ),
            )
          | ArrayBufferResponse(_) =>
            callback(
              Ok(
                eval(
                  ArrayBufferResponse(
                    xhr->Hermes_XHR.responseArrayBuffer->Js.Nullable.toOption,
                  ),
                ),
              ),
            )
          }
        },
      ),
    );

    xhr->Hermes_XHR.send;

    Some(() => {Hermes_XHR.abort(xhr)});
  };