import Digital from "pins/digital";
import WiFi from "wifi";
import { Server } from "http";

const magneticSensor = new Digital({
  pin: 5, //d1
  mode: Digital.InputPullDown,
});

new WiFi({
  ssid: "Fernando@Vero",
  password: "12345678",
});

const server = new Server({ port: 80 });
server.callback = function (msg, value, etc) {
  if (Server.prepareResponse == msg) {
    return {
      headers: ["Content-Type", "text/plain"],
      body: `${magneticSensor.read()}`,
    };
  }
};
