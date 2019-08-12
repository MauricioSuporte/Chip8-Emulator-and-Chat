var express = require("express"); 
var app = express();
var server = require("http").createServer(app);
var io = require("socket.io").listen(server);
//seta variáveis

memers = []; //array de usuários
memeConnections = []; //array de conexão

server.listen(process.env.PORT || 3000);  //Porta local
console.log("Server Online");

app.get("/", function(req, res){
	res.sendFile(__dirname + "/index.html"); //sincroniza com o html deste arquivo
});
	
io.sockets.on("connection", function(socket){
	//conexão
	memeConnections.push(socket);
	console.log("Usuário desconectado. Total de usuários: %s", memeConnections.length);
	
	//desconexão
	socket.on("disconnect", function(data){
	memers.splice(memers.indexOf(socket.username), 1); //acessa o array de usuários
	memeConnections.splice(memeConnections.indexOf(socket),1);
	console.log("Usuário conectado. Total de usuários: %s ", memeConnections.length);
	});

  socket.on("sendMessage", data => { 
    console.log(data);//Mostra o que os usuários escrevem no console
    io.sockets.emit("newMessage", data);
  });
});