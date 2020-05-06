module Client = Hermes_Client;
module Header = Hermes_Header;
module Method = Hermes_Method;
module QueryString = Hermes_QueryString;
module FormData = Hermes_FormData;
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
      onLoad:
        Some(
          data => {
            switch (data) {
            | Hermes_Types_ResponseType.Ok(data) =>
              callback(Ok(eval(data)))
            | Hermes_Types_ResponseType.Error(message) =>
              callback(Error(message))
            }
          },
        ),
    };
  };

let send:
  type a.
    Types.Client.t(Types.ResponseType.payload(a)) => option(unit => unit) =
  client => {
    let xhr = Hermes_XHR.make();

    let queryString =
      Belt.List.map(client.queryString, ((key, value)) => {
        key ++ "=" ++ value
      })
      ->Belt.List.toArray
      ->Js.Array.joinWith("&", _);

    let formData =
      Belt.List.map(client.formData, ((key, value)) => {key ++ "=" ++ value})
      ->Belt.List.toArray
      ->Js.Array.joinWith("&", _);

    let url =
      if (Js.List.isEmpty(client.queryString)) {
        client.url;
      } else {
        client.url ++ "?" ++ queryString;
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

    switch (client.onLoad) {
    | Some(onLoad) =>
      xhr->Hermes_XHR.addEventListener(
        `error(
          _ => {
            onLoad(Types.ResponseType.Error(xhr->Hermes_XHR.statusText))
          },
        ),
      );
      xhr->Hermes_XHR.addEventListener(
        `timeout(
          _ => {
            onLoad(Types.ResponseType.Error(xhr->Hermes_XHR.statusText))
          },
        ),
      );

      xhr->Hermes_XHR.addEventListener(
        `load(
          _ => {
            switch (client.responseType) {
            | Types.ResponseType.TextResponse(_) =>
              onLoad(
                Types.ResponseType.Ok(
                  Types.ResponseType.TextResponse(
                    xhr->Hermes_XHR.responseText->Js.Nullable.toOption,
                  ),
                ),
              )
            | Types.ResponseType.JSONResponse(_) =>
              onLoad(
                Types.ResponseType.Ok(
                  Types.ResponseType.JSONResponse(
                    xhr->Hermes_XHR.responseJson->Js.Nullable.toOption,
                  ),
                ),
              )
            | Types.ResponseType.DocumentResponse(_) =>
              onLoad(
                Types.ResponseType.Ok(
                  Types.ResponseType.DocumentResponse(
                    xhr->Hermes_XHR.responseDocument->Js.Nullable.toOption,
                  ),
                ),
              )
            | Types.ResponseType.ArrayBufferResponse(_) =>
              onLoad(
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
    | None => ()
    };

    if (Js.List.isEmpty(client.formData)) {
      xhr->Hermes_XHR.send;
    } else {
      xhr->Hermes_XHR.setRequestHeader(
        "Content-type",
        "application/x-www-form-urlencoded",
      );
      xhr->Hermes_XHR.sendString(formData);
    };

    Some(() => {Hermes_XHR.abort(xhr)});
  };