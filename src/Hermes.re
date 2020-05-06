module Client = Hermes_Client;
module Header = Hermes_Header;
module Method = Hermes_Method;
module QueryString = Hermes_QueryString;
module ResponseType = Hermes_ResponseType;
module Types = Hermes_Types;

let onLoad:
  type a.
    (
      Types.Client.t(Types.ResponseType.payload(a)),
      Types.ResponseType.t(a) => unit
    ) =>
    Types.Client.t(Types.ResponseType.payload(a)) =
  (client, callback) => {
    let eval: type a. Types.ResponseType.payload(a) => a =
      fun
      | Types.ResponseType.ArrayBufferResponse(b) => b
      | Types.ResponseType.DocumentResponse(d) => d
      | Types.ResponseType.JSONResponse(j) => j
      | Types.ResponseType.TextResponse(t) => t;

    {
      ...client,
      onLoad: data => {
        switch (data) {
        | Hermes_Types_ResponseType.Ok(data) => callback(Ok(eval(data)))
        | Hermes_Types_ResponseType.Error(message) =>
          callback(Error(message))
        };
      },
    };
  };

let send:
  type a.
    Types.Client.t(Types.ResponseType.payload(a)) => option(unit => unit) =
  client => {
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
        | OPTIONS => "OPTIONS"
        | GET => "GET"
        | HEAD => "HEAD"
        | POST => "POST"
        | PUT => "PUT"
        | DELETE => "DELETE"
        | TRACE => "TRACE"
        | CONNECT => "CONNECT"
        },
      (),
    );

    Belt.List.forEach(client.headers, ((key, value)) => {
      xhr->Hermes_XHR.setRequestHeader(key, value)
    });

    xhr->Hermes_XHR.addEventListener(
      `error(
        _ => {
          client.onLoad(Types.ResponseType.Error(xhr->Hermes_XHR.statusText))
        },
      ),
    );
    xhr->Hermes_XHR.addEventListener(
      `timeout(
        _ => {
          client.onLoad(Types.ResponseType.Error(xhr->Hermes_XHR.statusText))
        },
      ),
    );

    xhr->Hermes_XHR.addEventListener(
      `load(
        _ => {
          switch (client.response) {
          | Types.ResponseType.TextResponse(_) =>
            client.onLoad(
              Types.ResponseType.Ok(
                Types.ResponseType.TextResponse(
                  xhr->Hermes_XHR.responseText->Js.Nullable.toOption,
                ),
              ),
            )
          | Types.ResponseType.JSONResponse(_) =>
            client.onLoad(
              Types.ResponseType.Ok(
                Types.ResponseType.JSONResponse(
                  xhr->Hermes_XHR.responseJson->Js.Nullable.toOption,
                ),
              ),
            )
          | Types.ResponseType.DocumentResponse(_) =>
            client.onLoad(
              Types.ResponseType.Ok(
                Types.ResponseType.DocumentResponse(
                  xhr->Hermes_XHR.responseDocument->Js.Nullable.toOption,
                ),
              ),
            )
          | Types.ResponseType.ArrayBufferResponse(_) =>
            client.onLoad(
              Types.ResponseType.Ok(
                Types.ResponseType.ArrayBufferResponse(
                  xhr->Hermes_XHR.responseArrayBuffer->Js.Nullable.toOption,
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