cleverbot
=========

An IRC bot implemented using C++11 and Boost.Asio

Working features
=========

By now the bot can connect to a IRC network, join channels, send private 
messages, change nick and quit. Here is a list of commands:

* /m subject message - send a message to the subject (#channel, nick, etc.)
* /n newnick         - changes the bot's nickname
* /j #channel        - tries to join the channel #channel
* /q message         - quits leaving a message
 