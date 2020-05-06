# Table of contents

- [What is it?](#what-is-it)
- [What state is it in?](#what-state-is-it-in)
- [How do I install it?](#how-do-i-install-it)
- [API](#api)
  - [Methods](#methods)
  - [Query Strings](#query-strings)
  - [Form Data](#form-data)
  - [Headers](#headers)
  - [Response Types](#response-types)
  - [Sending a Request](#sending-a-request)
  - [Cancelling Requests](#cancelling-requests)
  - [Complete Example](#complete-example)
- [Credits](#credits)

# What is it?

Hermes (the name is subject to change) is a Bucklescript library enabling http-requests over XMLHttpRequests.

# What state is it in?

This is still highly experimental and untested.

Please do not use it in production yet.

### TODOs:

- [x] Url
- [x] Methods
  - [x] OPTIONS
  - [x] GET
  - [x] HEAD
  - [x] POST
  - [x] PUT
  - [x] DELETE
  - [x] TRACE
  - [x] CONNECT
- [x] Headers
  - [x] set
  - [x] add
  - [x] delete
- [x] Query Strings
  - [x] set
  - [x] add
  - [x] delete
- [x] Form Data / Body
  - [x] set
  - [x] add
  - [x] delete
- [x] Response Types
  - [x] ArrayBuffer `Js.Typed_array.ArrayBuffer.t`
  - [ ] Blob
  - [x] Document `Dom.document`
  - [x] Json `Js.Json.t`
  - [x] Text `string`
- [x] Events
  - [x] `onLoad`
  - [ ] `onProgress`
  - [ ] `onAbort`
- [x] send
- [x] abort
- [ ] async
- [ ] overrideMimeType
- [ ] timeout
- [ ] auth (username / password)
- [ ] withCredentials
- [ ] upload
- [ ] statusCode

# How do I install it?

```
yarn add @space-labs/hermes
```

or

```
npm install @space-labs/hermes --save
```

Then add `@space-labs/hermes` as a dependency to `bsconfig.json`:

```diff
"bs-dependencies": [
+  "@space-labs/hermes"
]
```

# API

### Methods

```reason
Hermes.Method.options("https://domain.com/");
Hermes.Method.get("https://domain.com/");
Hermes.Method.head("https://domain.com/");
Hermes.Method.post("https://domain.com/");
Hermes.Method.put("https://domain.com/");
Hermes.Method.delete("https://domain.com/");
Hermes.Method.trace("https://domain.com/");
Hermes.Method.connect("https://domain.com/");
```

### Query Strings

```reason
client->Hermes.QueryString.set([("key", "value"), ("key2", "value2")]);
client->Hermes.QueryString.add("key", "value");
client->Hermes.QueryString.remove("key");
```

### Form Data

```reason
 client->Hermes.FormData.set([("key", "value"), ("key2", "value2")]);
 client->Hermes.FormData.add("key", "value");
 client->Hermes.FormData.remove("key");
```

### Headers

```reason
client->Hermes.Header.set([("key", "value"), ("key2", "value2")]);
client->Hermes.Header.add("key", "value");
client->Hermes.Header.remove("key");
```

### Handling Responses

The datatype of the response is based on the currently set `ResponseType` (`option(string)` by default).

```reason
client->Hermes.onLoad(response => {
  switch (response) {
  | Ok(Some(data)) => Js.Console.log(data)
  | Ok(None) => Js.Console.info("Response was empty")
  | Error(message) => Js.Console.error(message)
  }
});
```

### Response Types

If you want to change the `ResponseType`, you have to do it **before** the `onLoad`. If you set it afterwards, your
`onLoad` will be removed (because it would assume a wrong type signature).

| ResponseType | PayloadType                          |
| ------------ | ------------------------------------ |
| Text         | option(string)                       |
| Json         | option(Js.Json.t)                    |
| Document     | option(Dom.document)                 |
| ArrayBuffer  | option(Js.Typed_array.ArrayBuffer.t) |

```reason
client->Hermes.ResponseType.setText; // default
client->Hermes.ResponseType.setJson;
client->Hermes.ResponseType.setDocument;
client->Hermes.ResponseType.setArrayBuffer;
```

### Sending a Request

```reason
client->Hermes.send;
```

### Cancelling Requests

`Hermes.send` returns a function, with which you may cancel the current request. It has a signature of
`option(unit => unit)`, so you don't have to do anything when using it inside `React.useEffect`.

```reason
  /* React */
  React.useEffect(() => {
    Hermes.Method.get("https://domain.com/")->Hermes.send
  });

  /* Plain Reason */
  let maybeCancel = Hermes.Method.get("https://domain.com/")->Hermes.send;
  switch(maybeCancel) {
    | Some(cancel) => cancel();
    | None => ();
  };
```

### Complete Example

```reason
Hermes.Method.get("http://localhost:8081/")
->Hermes.ResponseType.setJson
->Hermes.QueryString.set([
    ("firstname", "Max"),
    ("lastname", "Mustermann"),
    ("username", "max"),
    ("email", "max@mustermann.de"),
  ])
->Hermes.Header.add("authorization", "Bearer 123")
->Hermes.onLoad(response => {
    switch (response) {
    | Ok(Some(data)) => Js.Console.log(data)
    | Ok(None) => Js.Console.info("No Response!")
    | Error(message) => Js.Console.error(message)
    }
  })
->Hermes.send;
```

## Credits

[Request - Simplified HTTP client](https://github.com/request/request) for inspiration

**@hgiraud** on Discord had some nice suggestions regarding the API
