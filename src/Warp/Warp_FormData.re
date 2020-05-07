open Warp_Types_Client;

let add = (client, key, value) => {
  {...client, formData: [(key, value), ...client.formData]};
};

let set = (client, formData) => {
  {...client, formData};
};

let remove = (client, keyToRemove) => {
  {
    ...client,
    formData:
      Belt.List.keep(
        client.formData,
        formData => {
          let (key, _value) = formData;
          key !== keyToRemove;
        },
      ),
  };
};