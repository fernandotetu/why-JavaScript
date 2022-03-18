import WiFi from "wifi";
import Analog from "pins/analog";
import { Request } from "http";

setWakeUpTime();

new WiFi(
  {
    ssid: "xxx",
    password: "xxx",
  },
  function (status) {
    if (status == WiFi.gotIP) {
      // network is ready  
      const value = readTemp();
      sendData( value)
    }
  }
);

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

function readTemp() {
  const readedValue = Analog.read(0);
  return ((readedValue / 1024.0) * 3300) / 10;
}

// native interface to ESP-IDF (see main.c file)
function setWakeUpTime() @ "xs_setWakeUpTime";
function sleep() @ "xs_sleep";
