#ifndef SERVER_HPP
#define SERVER_HPP

#include "Location.hpp"

class response;

class Request {

	public :
		string		method;
		string		path;
		string		_req;
		string		query_str;
		string		http_version;
		Location	_location;
		mapstring	_error_page;
		string		_buffer;
		int			_first;
		size_t		_size_to_write;
		size_t		_amount_written;
		size_t		_size_recv;
		string		get_error_page(string code);
		int			_fd;
		int			_buffer_state;
		int			socket;
		string		code;
		size_t		_file_size;
		string		host;
		string		body;
		mapstring	headers;
		string		getHeader(string key);
};

struct Client
{
	socklen_t				address_length;
	struct sockaddr_storage	address;
	int						socket;
	int						received;
	bool					isSending;
	Request					request;
};


class Server
{
	private:
		mapstring				_elements;
		mapstring				_error_page;
		locationmap				_location;
		SOCKET					socket_listen;
		struct addrinfo 		hints;
		struct addrinfo 		*bind_address;
		response				*res;
		int						r;
	public:
		std::vector<Client>		clients;
		void					reset();
		int						find_element(string key);
		void					set_element(string key, string &value);
		string 					get_element(string key);
		Location				matchlocation(string &location);
		void					setting_PORT();
		void					recieve_cnx(fd_set &reads, fd_set &writes);
		Server					server_fill(std::ifstream &ifs, string &line);
		void					must_fill();
		int						getSocket();
};


int isValidRequestURI(const std::string &uri);
int checkUriLength(const std::string &uri);
int checkRequestBodySize(const std::string &body, size_t max_allowed);
void parse(Request &server, string request);

#endif