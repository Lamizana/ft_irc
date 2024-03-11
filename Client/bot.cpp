#include "Client.hpp"

void		Server::bot( Client client ){

    if (client.getCmdBuf().size() == 1)
        return;

    srand( time( NULL ) );
    int i = rand() % 3 + 1;

	std::string POWER = "";
    if (i == 1)
		POWER = "ROCK";
	else if (i == 2)
		POWER = "PAPER";
    else 
		POWER = "SCISSORS";

	std::string toSend = ":BOT PRIVMSG BOT " + POWER + " \r\n";
    
    std::string TMP = client.getCmdBuf()[1];
	size_t j = TMP.find(":");
	if (j != std::string::npos)
		TMP = TMP.substr(2);

	send(client.getSocket(), toSend.c_str(),toSend.size(), 0);

	if ((POWER == "ROCK" && TMP == "PAPER") || (POWER == "PAPER" && TMP == "SCISSORS") || (POWER == "SCISSORS" && TMP == "ROCK")){
		std::string toSend = ":BOT PRIVMSG BOT You won, I lost \r\n";
		send(client.getSocket(), toSend.c_str(),toSend.size(), 0);
	} else if ((POWER == "PAPER" && TMP == "ROCK") || (POWER == "SCISSORS" && TMP == "PAPER") || (POWER == "ROCK" && TMP == "SCISSORS")){
		std::string toSend = ":BOT PRIVMSG BOT You lost, I won \r\n";
		send(client.getSocket(), toSend.c_str(),toSend.size(), 0);
	} else if ((POWER == "PAPER" && TMP == "PAPER") || (POWER == "ROCK" && TMP == "ROCK") || (POWER == "SCISSORS" && TMP == "SCISSORS")){
		std::string toSend = ":BOT PRIVMSG BOT It is a DRAW \r\n";
		send(client.getSocket(), toSend.c_str(),toSend.size(), 0);
	} else {
		std::string toSend = ":BOT PRIVMSG BOT ROCK, PAPER OU SCISSORS ?\r\n";
		send(client.getSocket(), toSend.c_str(),toSend.size(), 0);
	}
	return;
}