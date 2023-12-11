# Four grade levels
## Level 1 - C-: Implement a client/server app where two or more anonymous users can chat.
Server must be setup to listen on port 25565
Client – when staring the client app, provide an username and the server name. The client app must use the same port as the server. The username is local to the client and may not be unique among the clients. The username is added to the beginning of the message being sent to the server during a chat. The server does not manage names (or anything else). The server receives a message from a client then sends the message to the other client (or to all clients connected). To disconnect from the server, the client should send QUIT message (see IRC protocol below).

## Level 2: C/C+At this level, the server has more responsibility. When the client starts, the app will output a prompt.
A client must use the USER command below to connect to the sever. The server maintains a list of unique names. If a names is already taken and error message will be sent back to the client. The server will also send back an error if there are not enough parameters provided.

### USER Command
•Command: USER   
•Parameters:```<username> <hostname> <servername> <realname>```  
•Example: USER guest tolmoon tolsun Ronnie Reagan  
•Possible numeric server replies:  
•ERR_NEEDMOREPARAMS  
•ERR_ALREADYREGISTRED  

The USER message is used at the beginning of connection to specify the username, hostname, servername and
realname of the new user. The hostname is the name of the client’s machine.

## Level 3: B-/B – All of Level 2 and multi-user without channels.

## Level 4: B+/A – All of Level 3 and the IRC commands.
User proper documentation. Keep functions length to 20 lines or less. The code examples presented do not
necessarily follow this rule, they are just examples to demonstrate how to utilize certain functions related to socket programming and a client/server app.

# IRC Project Requirements
The IRC (Internet Relay Chat) protocol has been designed over a number of years for use with text-based
conferencing. Although no encoding standard is specified, ASCII or UTF-8 is recommended. 

## Servers 
The server forms the backbone of IRC, providing a point to which clients may connect to to talk to each other.

## Clients
A client is anything connecting to a server that is not another server. The server MUST have the following
information about all clients:
1. A unique client identifier (a.k.a. the client "nickname", a string between 1 and 9 characters) 
2. the real name of the host that the client is running on 
3. the username of the client on that host 
4. the server to which the client is connected 

## Channels
A channel is a named group of one or more clients which will all receive messages addressed to that channel. The
channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it. While channel exists, any client can reference the channel using the name of the channel.
Channels names are strings between 1 and 200 characters. Channel names must start with a # and may not contain
whitespaces nor commas. As part of the protocol, a user may be a part of several channels at once, but a limit of
ten (10) channels is recommended.

## Channel Operators
The channel operator (also referred to as a "chop" or "chanop") on a given channel is considered to 'own' that
channel and is identified by the @ prefix before their name on all message. The channel operator is privileged to
the following commands. When the channel operator parts from the channel, the channel operator is changed to
another member of the channel (a good choice is the first person to join after the channel was created.)

## Command Function
```KICK``` Eject a client from the channel  
```TOPIC``` Change the channel topic?  

## Messages
Servers and clients send each other messages which may or may not generate a reply. If the message contains a
valid command, the client should expect a reply. The most common server reply is the numeric reply, used for both
errors and normal replies.
IRC messages are always lines of characters terminated with a CR-LF (Carriage Return - Line Feed) pair, and
these messages shall not exceed 512 characters in length, counting all characters including the trailing CR-LF.
Thus, there are 510 characters maximum allowed for the command and its parameters. There is no provision for
continuation message lines.

## Commands: Connection Registration
Descriptions of messages related to connection registration and deregistration.

### USER Command
•Command: USER  
•Parameters:```<username> <hostname> <servername> <realname>```    
•Example: USER guest tolmoon tolsun Ronnie Reagan  
•Possible numeric server replies:   
•ERR_NEEDMOREPARAMS  
•ERR_ALREADYREGISTRED  

The USER message is used at the beginning of connection to specify the username, hostname, servername and
realname of the new user.

### QUIT Command
•Command: QUIT  
•Parameters: ```[<quit message>]```   
•Example: QUIT got to go, goodbye! A client session is ended with a quit message. The server must close
the connection to a client which sends a QUIT message. If a "Quit Message" is given, this will be sent
instead of the default message, the nickname.  
If, for some other reason, a client connection is closed without the client issuing a QUIT command (e.g. client dies
and EOF occurs on socket), the server is required to fill in the quit message with some sort of message reflecting
the nature of the event which caused it to happen. 
Commands: Channel Operations 
Messages related to managing channels. 

### JOIN Command
•Command: JOIN  
•Parameters:```<channel>{,<channel>}```   
•Example: JOIN #foobar   
•Possible numeric server replies:   
•ERR_CHANNELISFULL  
•ERR_NOSUCHCHANNEL   
•ERR_TOOMANYCHANNELS  

The JOIN command is used by client to start listening a specific channel. Once a user has joined a channel, they
receive notice about all commands their server receives which affect the channel. If a JOIN is successful, the user
is then sent the channel's topic (using RPL_TOPIC) and the list of users who are on the channel (using
RPL_NAMREPLY), which must include the user joining.

### PART Command
•Command: PART  
•Parameters:```<channel>{,<channel>}```   
•Example: PART #twilight_zone, #networking-study-group  
•Possible numeric server replies:  
•ERR_NEEDMOREPARAMS  
•ERR_NOSUCHCHANNEL  
•ERR_NOTONCHANNEL  

The PART message causes the client sending the message to be removed from the list of active users for all given
channels listed in the parameter string.

### TOPIC Command
•Command: TOPIC  
•Parameters:```<channel> [<topic>]```   
•Example:  
•Possible numeric server replies:  
•ERR_NEEDMOREPARAMS   
•ERR_NOTONCHANNEL  
•RPL_NOTOPIC  
•RPL_TOPIC  

The TOPIC message is used to change or view the topic of a channel. The topic for channel <channel> is returned
if there is no <topic> given. If the <topic> parameter is present, the topic for that channel will be changed.

### NAMES Command
•Command: NAMES  
•Parameters: ```[<channel>{,<channel>}]```   
•Example: NAMES #twilight_zone,#42  
•Possible numeric server replies:  
•RPL_NAMREPLY  
•RPL_ENDOFNAME Returns all the nicknames of the specified channels.  

The <channel> parameter specifies which channel(s) to return information about if valid. There is no error reply for
bad channel names.

If no <channel> parameter is given, a list of all channels and their occupants is returned. At the end of this list, a list of users who are visible but either not on any channel.

### LIST Command
•Command: LIST  
•Parameters: ```[<channel>{,<channel>} [<server>]]```    
•Example: LIST #twilight_zone,#42   
•Possible numeric server replies:   
•ERR_NOSUCHSERVER   
•RPL_LISTSTART   
•RPL_LIST  
•RPL_LISTEND   

If no <channel> parameter is given, the list message is used to list channels and their topics. If the <channel>
parameter is used, only the status of that channel is displayed.

### KICK Command
•Command: KICK    
•Parameters: ```<channel> <user> [<comment>]```    
•Example: KICK Melbourne Matthew   
•Possible server numeric replies:    
•ERR_NEEDMOREPARAMS  
•ERR_NOSUCHCHANNEL  
•ERR_CHANOPRIVSNEEDED  
•ERR_NOTONCHANNEL  

The KICK command can be used to forcibly remove a user from a channel. It 'kicks them out' of the channel
(forced PART). Only a channel operator may kick another user out of a channel. The server must check that it is
valid (i.e. the sender is actually a channel operator) before removing the victim from the channel.

### NICK Command
•Command: NICK  
•Parameters: ```<nickname>```   
•Example: NICK Wiz  
•Possible numeric server replies:  
•ERR_NONICKNAMEGIVEN  
•ERR_NICKCOLLISION  

NICK message is used to give user a nickname or change the previous one. If a NICK message arrives at a server
which already knows about an identical nickname for another client, a nickname collision occurs
(ERR_NICKCOLLISION).