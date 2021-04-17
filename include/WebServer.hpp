#pragma once

#include "AServer.hpp"
#include "Request.hpp"
#include <map>

#ifdef __linux__
#define CGI_PATH "./ubuntu_cgi_tester"
#else
#define CGI_PATH "./cgi_tester"
#endif

class ConfigParse;
class Response;

class WebServer : public AServer
{
private:
	std::map<int, Request*> requests;

	std::map<int, std::string> reqStr;
	ConfigParse &conf;

public:
	WebServer(ConfigParse &conf);

	virtual void OnRecv(int fd, std::string const &str);
	virtual void OnSend(int fd);
	virtual void OnAccept(int fd, int port);
	virtual void OnDisconnect(int fd);

	virtual void OnFileRead(int fd, std::string const &str);
	virtual void OnFileWrite(int fd);

	virtual ~WebServer();

	void request_process(int fd, Request &req);
	void cgi_stub(std::string const &path, Request &req, std::string &result);

	void methodGET(Response &res, std::string req_path);
	void methodHEAD(Response &res, std::string req_path);
	void methodPUT(Response &res, Request &req);
	void methodPOST(Response &res, Request &req);
	void methodInvalid(Response &res, Request &req);
};
