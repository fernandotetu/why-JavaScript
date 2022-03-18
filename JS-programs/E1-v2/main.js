import WiFi from "wifi";
import Analog from "pins/analog";
import { Request } from "http";

new WiFi(
  {
    ssid: "xxx",
    password: "xxx",
  },
  function (status) {
    if (status == WiFi.gotIP) {
      // network is ready
      System.setInterval(() => {
        // network is ready
        const value = readTemp();
        sendData(value);
      }, 20000); // repeat each 20 secs
    }
  }
);

function readTemp() {
  const readedValue = Analog.read(0);
  return ((readedValue / 1024.0) * 3300) / 10;
}

function sendData(temp) {
  let request = new Request({
    host: "api.thingspeak.com",
    path: `/update?api_key=<HIDE>=${temp}`,
    response: String,
  });
  request.callback = function (message, value, etc) {
    if (Request.responseComplete == message) {
      // go to sleep
      sleep();
    }
  };
}
