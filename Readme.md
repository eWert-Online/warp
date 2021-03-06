# Warp

Warp is a Bucklescript library enabling http-requests over XHR.

If you find a bug or think some feature is missing, don't hesitate to file an issue or even a pull request.

Every little bit of help is very welcome!

# Table of contents

- [How do I install it?](#how-do-i-install-it)
- [API](#api)
  - [Methods](#methods)
  - [Settings](#settings)
  - [Query Strings](#query-strings)
  - [Form Data](#form-data)
  - [Headers](#headers)
  - [Events](#events)
  - [Response Types](#response-types)
  - [Sending a Request](#sending-a-request)
  - [Cancelling Requests](#cancelling-requests)
  - [Complete Example](#complete-example)
- [What state is it in?](#what-state-is-it-in)
- [Credits](#credits)

# How do I install it?

```
yarn add @space-labs/warp
```

or

```
npm install @space-labs/warp --save
```

Then add `@space-labs/warp` as a dependency to `bsconfig.json`:

```diff
"bs-dependencies": [
+  "@space-labs/warp"
]
```

# API

### Methods

```reason
Warp.Method.options("https://domain.com/");
Warp.Method.get("https://domain.com/");
Warp.Method.head("https://domain.com/");
Warp.Method.post("https://domain.com/");
Warp.Method.put("https://domain.com/");
Warp.Method.delete("https://domain.com/");
Warp.Method.trace("https://domain.com/");
Warp.Method.connect("https://domain.com/");
```

### Settings

```reason
client->Warp.Settings.async(false);
client->Warp.Settings.timeout(5000);
client->Warp.Settings.withCredentials(true);
client->Warp.Settings.auth("user", "password");
client->Warp.Settings.overrideMimeType("text/plain");
```

### Query Strings

```reason
client->Warp.QueryString.set([("key", "value"), ("key2", "value2")]);
client->Warp.QueryString.add("key", "value");
client->Warp.QueryString.remove("key");
```

### Form Data

```reason
 client->Warp.FormData.set([("key", "value"), ("key2", "value2")]);
 client->Warp.FormData.add("key", "value");
 client->Warp.FormData.remove("key");
```

### Headers

```reason
client->Warp.Header.set([("key", "value"), ("key2", "value2")]);
client->Warp.Header.add("key", "value");
client->Warp.Header.remove("key");
```

### Events

**onProgress**

```reason
client->Warp.Event.onProgress(_event => {
  Js.Console.log("We are making progress!")
});
```

**onLoad**

The datatype of the response is based on the currently set `ResponseType` (`option(string)` by default).

```reason
client->Warp.Event.onLoad(response => {
  switch (response) {
  | Belt.Result.Ok(Some(data)) => Js.Console.log(data)
  | Belt.Result.Ok(None) => Js.Console.info("Response was empty")
  | Belt.Result.Error(message) => Js.Console.error(message)
  }
});
```

**onLoadWithStatusCode**

Same as `onLoad` but gets the requests statusCode as a second argument

```reason
client->Warp.Event.onLoadWithStatusCode((response, statusCode) => {
  switch (response) {
  | Belt.Result.Ok(Some(data)) => Js.Console.log2(data, statusCode)
  | Belt.Result.Ok(None) => Js.Console.info2("No Response!", statusCode)
  | Belt.Result.Error(message) => Js.Console.error2(message, statusCode)
  }
});
```

**onAbort**

```reason
client->Warp.Event.onAbort(() => {
  Js.Console.log("The request got aborted :(")
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
client->Warp.ResponseType.setText; // default
client->Warp.ResponseType.setJson;
client->Warp.ResponseType.setDocument;
client->Warp.ResponseType.setArrayBuffer;
```

### Sending a Request

```reason
client->Warp.send;
```

### Cancelling Requests

`Warp.send` returns a function, with which you may cancel the current request. It has a signature of
`option(unit => unit)`, so you don't have to do anything when using it inside `React.useEffect`.

```reason
  /* React */
  React.useEffect(() => {
    Warp.Method.get("https://domain.com/")->Warp.send
  });

  /* Plain Reason */
  let maybeCancel = Warp.Method.get("https://domain.com/")->Warp.send;
  switch(maybeCancel) {
    | Some(cancel) => cancel();
    | None => ();
  };
```

### Examples

**Basic**

```reason
Warp.Method.get("http://localhost:8081/")
->Warp.ResponseType.setJson
->Warp.QueryString.set([
    ("firstname", "Max"),
    ("lastname", "Mustermann"),
    ("username", "max"),
    ("email", "max@mustermann.de"),
  ])
->Warp.Header.add("authorization", "Bearer 123")
->Warp.Event.onLoad(response => {
    switch (response) {
    | Belt.Result.Ok(Some(data)) => Js.Console.log(data)
    | Belt.Result.Ok(None) => Js.Console.info("No Response!")
    | Belt.Result.Error(message) => Js.Console.error(message)
    }
  })
->Warp.send;
```

**Sending JSON**

```reason
let stringifiedJson =
  Js.Dict.fromList([
    ("query", Js.Json.string(operation.text)),
    ("variables", variables),
  ])
  ->Js.Json.object_
  ->Js.Json.stringify;

Warp.Method.post("http://localhost:8081/")
->Warp.ResponseType.setJson
->Warp.FormData.setJson(stringifiedJson)
->Warp.Header.add("authorization", "Bearer 123")
->Warp.Event.onLoad(response => {
    switch (response) {
    | Belt.Result.Ok(Some(data)) => Js.Console.log(data)
    | Belt.Result.Ok(None) => Js.Console.info("No Response!")
    | Belt.Result.Error(message) => Js.Console.error(message)
    }
  })
->Warp.send;
```

# What state is it in?

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
  - [x] setJson
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
  - [x] `onLoadWithStatusCode`
  - [x] `onProgress`
  - [x] `onAbort`
- [x] Settings
  - [x] async
  - [x] timeout
  - [x] withCredentials
  - [x] auth (username / password)
  - [x] overrideMimeType
- [x] send
- [x] abort
- [ ] upload
- [ ] tests

## Credits

[Request - Simplified HTTP client](https://github.com/request/request) for inspiration

**@hgiraud** on Discord had some nice suggestions regarding the API
