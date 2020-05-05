# What is it?

Hermes is a Bucklescript library enabling http-requests over XMLHttpRequests.

# What state is it in?

This is still highly experimental and untested.

Please do not use it in production yet.

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

# How do I use it?

### Example

```reason
Hermes.get("http://localhost:8081/")
->Hermes.setQueryString([
    ("firstname", "Max"),
    ("lastname", "Mustermann"),
    ("username", "max"),
    ("email", "max@mustermann.de"),
  ])
->Hermes.setHeaders([("authorization", "Bearer 123")])
->Hermes.setResponseTypeJSON
->Hermes.onLoad(response => {
    switch (response) {
    | Ok(Some(data)) => Js.Console.log(data)
    | Ok(None) => Js.Console.info("No Response!")
    | Error(message) => Js.Console.error(message)
    }
  })
->Hermes.send;
```
