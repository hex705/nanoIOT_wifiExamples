// /*
// note this is my first web-app build in glitch
//  it likely has some issues
//
//  if you remixed this you need a shiftr URL in the
//  .env file
//  var name is ::
//
//  process.env.SHIFTR_URL -- you will need to supply a value from shiftr
//  it will be the url presented at end of token creation -- full url
//
//  you also need to pick a parser -- Arduino can use JSON, raw or maybe OSC
//
// */
//
// // first part of this is from shifman -- code train socket servers
// // proper links etc coming
//
// const env = require('dotenv');
// env.config();
//
// const PORT = process.env.PORT || 3009;
//
// var express = require('express');
//
// var app = express();
//
// var server = app.listen(PORT);
//
// app.use(express.static('public'));
//
// console.log("my socket server is running on Port :: " + PORT);
//
//
// // _______________________________________________________
// // fancy socket server
// // it 'upgrades' connection, listens for data and draws it
// // _______________________________________________________
//
// // create a web socket server -- sockets let node talk to web pages
// var socket = require('socket.io');
// var io = socket(server);
//
//
// //new stuff from  ::  https://stackoverflow.com/questions/10275667/socket-io-connected-user-count
//
// // create a listener for the web socket -- this listens for WEB clients only
// // this does not listen to MQTT or processing actions.
//
// io.sockets.on('connection', newConnection);
//
// // create a function that handles incoming messages to the server
// // and passes them out to all the clients as needed
// function newConnection (socket) {
//
//   // for debug
//   //console.log(' new connection: ' + socket.id + " total connections == " + connectCounter);
//
//   // send to MQTT for non-web connections
//   //mqttSend(connectCounter);
//
//   // event handler for messages FROM web pages
//   socket.on('topic1', handleTopic1); // eventType, fxn
//
//   // i need to unpack where callbacks can go structurally -- do tehy have to be in newCOnnection ?
//   // call back for data labelled 'mouse' -- you can use any label
//   function handleTopic1(data){
//     console.log(' in server handleTopic1 with ',data);
//
//     //send to all the other clients -- but not the source
//     socket.broadcast.emit('topic1', data);
//     // alt ::  send to all clients including echo to source
//     // io.sockets.emit('mouse',data);
//
//     // call this function to send web data to processing via shiftr (MQTT)
//     mqttSend(data);
//
//     //console.log(data);
//   }
//
//   socket.on('disconnect', function() {
//
//   });
//
// }
//
// // this code provides a bridge to shiftr.
//
// const mqtt = require('mqtt'); // mqtt is included in dependecies of JSON file
//
// // did you remix this ??  you need to put your SHIFTR URL in .env file
// // you can get the right URL from secret tab of processing sketch
// // if you don;t have my processing file -- get one from shiftr directly
//
// // the URL is the url presented at end of token process
//
// let mqttClient = mqtt.connect(process.env.SHIFTR_URL, {clientId: 'JSNODEserver_sd'}); // glitch is just a label
//
// // event handles for connect to shiftr and message received
// mqttClient.on('connect', mqttConnect);
// mqttClient.on('message', incomingMqttMessage); // message is generic handler
//
// function mqttConnect(e) {
//
//   console.log('connected to shiftr!');
//
//   mqttClient.subscribe('topic1'); // subscribe to published topics
//   mqttClient.subscribe('topic2');
//   //setInterval(function() {
//   //  client.publish('jsMouse');
//   //}, 5000);
//
// }
//
//
// // when you get subscribed message, content shows up here
// function incomingMqttMessage(topic, message) {
//
//   // need topic routing here as required by project
//   console.log('in incomingMqttMessage --> topic : '+ topic + '-- message : ' + message);
//
//
//   switch (topic){
//     case 'topic1':
//       console.log('top1');
//     break;
//     case 'topic2':
//       console.log('top2');
//     break;
//     default:
//   }
//
//   //parse the message -- assumes JSON -- which is out there.
//   //let mParse = JSON.parse(message);
//   //  console.log('server parse out x ::' + mParse.x)
//   //  let mData = {
//   //    x:mParse.x,
//   //    y:mParse.y,
//   //    z:mParse.z
//   //  }
//
//   //this message came from Arduinovia MQTT - shiftr
//   //this line shares it with WEB clients
//   //note use of emit and (sockets -- plural )
//
//   //  io.sockets.emit('mqtt', mData);// https://stackoverflow.com/questions/8281382/socket-send-outside-of-io-sockets-on
// }
//
//
//
// // this fxn is called from inside the socket above
// // this fxn takes WEB client data and PUBLISHES it to shiftr so processing can pick it up.
//
// function mqttSend(messageToSend){
//   console.log('messageToSend ',messageToSend);
//   // data is jason and we need to unpack it and reconfigure for MQTT string transport
//   let thisTopic = messageToSend.topic;
//   let messageBody = messageToSend.str;
//
//   console.log('thisTopic ',thisTopic);
//   console.log('messageBody ', messageBody);
//   // // stringify is needed bc data is a JSON <OBJECT> -- and MQTT lib needs a String
//   // var data = {
//   //   cc: connectCounter
//   // }
//   //
//   // let s = JSON.stringify(data); // https://stackoverflow.com/questions/4162749/convert-js-object-to-json-string
//   //console.log('server mqttSend ' + s);
//   mqttClient.publish(thisTopic, messageBody);// topic, data
// }
