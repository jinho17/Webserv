#include "EchoServer.hpp"
#include "RequestParser.hpp"
#include "Response.hpp"
#include "ChunkParser.hpp"
#include <iostream>

void EchoServer::OnRecv(int fd, std::string const &str)
{
	using namespace std;
	(void)fd;



	cout << "-------str----------\n";
	cout << str.substr(0,100) << endl;
	cout << "===================\n";
	RequestParser req(str);
	Response res("jachoi server");
	switch (req.getMethodType())
	{
		case GET:
		{
			cout << "=path=====================================\n";
			cout <<  req.pathparser->path << endl;
			cout << "==========================================\n";
			if (req.pathparser->path == "/directory/oulalala")
			{
				sendStr(fd, res.makeResFromText(404, "ss"));
				disconnect(fd);
				return;
			}
			else if (req.pathparser->path == "/directory/nop/other.pouac")
			{
				sendStr(fd, res.makeResFromText(404, "ss"));
				disconnect(fd);
				return;
			}
			else if (req.pathparser->path == "/directory/Yeah")
			{
				sendStr(fd, res.makeResFromText(404, "ss"));
				disconnect(fd);
				return;
			}
			sendStr(fd, res.makeResFromText(200, "hello world"));
			disconnect(fd);
			break;
		}
		case POST:
		{
			if (req.pathparser->path == "/directory/youpi.bla")
			{
				std::string s =  ChunkParser(req.body).getData();
				cout << "s: " << s.length() << endl;
				// cout << s.substr(0, 100) << endl;
				sendStr(fd, res.makeResFromText(200, s));
				disconnect(fd);
				return;
			}
			sendStr(fd, res.makeResFromText(405, "1"));
			disconnect(fd);
			break;
		}
		case HEAD:
		{
			sendStr(fd, res.makeResFromText(405, "1"));
			disconnect(fd);
			break;
		}
		case PUT:
		{
			ChunkParser chunk(req.body);
			cout << chunk.getData().size() << endl;
			// cout << chunk.getData() << endl;
			sendStr(fd, res.makeResFromText(200, chunk.getData()));
		}
	}
	// for (std::map<string, string>::iterator it = req.header.begin(); it != req.header.end() ; it++)
	// 	cout << it->first << ": " << it->second << endl;
	// cout << "body: " <<  req.body << endl;
}

void EchoServer::OnSend(int fd)
{
	(void)&fd;
}

void EchoServer::OnAccept(int fd, int port)
{
	(void)&fd;
	(void)&port;
	std::cout << fd << "(" << port << "): accepted!" << "\n";
}

void EchoServer::OnDisconnect(int fd)
{
	(void)&fd;
	std::cout << fd << ": disconnected!" << "\n";
}
