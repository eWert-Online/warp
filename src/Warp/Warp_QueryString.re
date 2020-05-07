open Warp_Types_Client;

let add = (client, key, value) => {
  {...client, queryString: [(key, value), ...client.queryString]};
};

let set = (client, queryString) => {
  {...client, queryString};
};

let remove = (client, keyToRemove) => {
  {
    ...client,
    queryString:
      Belt.List.keep(
        client.queryString,
        queryString => {
          let (key, _value) = queryString;
          key !== keyToRemove;
        },
      ),
  };
};