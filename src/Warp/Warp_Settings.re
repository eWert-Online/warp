open Warp_Types_Client;

let withCredentials = (client, withCredentials) => {
  {...client, withCredentials};
};

let async = (client, async) => {
  {...client, async};
};

let timeout = (client, timeout) => {
  {...client, timeout};
};