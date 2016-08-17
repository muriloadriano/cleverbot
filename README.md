cleverbot
=========

An extensible IRC bot implemented using C++11 and Boost.Asio.

Working features
=========

By now the bot can connect to a IRC network, join channels, send private 
messages, change nick and quit. Here is a list of commands:

* /m subject message - send a message to the subject (#channel, nick, etc.)
* /n newnick         - changes the bot's nickname
* /j #channel        - tries to join the channel #channel
* /q message         - quits leaving a message

In the code side, it is possible to add read handlers, for example:

```
bot.add_read_handler([&bot](const std::string& m) {
	std::istringstream iss(m);
	std::string from, type, to, msg;
	
	iss >> from >> type >> to >> msg;
	
	if (msg == ":!time") {
		std::time_t now = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now());
			
		bot.message(to, std::ctime(&now));
	}
});
```

This method call adds a read handler (a lamda function which takes an 
`const std::string` as argument) to the bot which prints the current time 
whenever some user sends a !time message on a channel in which the bot is in.

Building
=========
```
cmake .
make all
```


Running
=========
```
./bin/release
```

- [1] - C++11 on Wikipedia - http://en.wikipedia.org/wiki/C%2B%2B11
- [2] - Boost libraries - http://www.boost.org/
