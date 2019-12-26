# P2P Instagram
## Project for the Distributed Systems Course in the American University in Cairo.
### Overview
Full implementation of the Request-Reply Protocol and the RPC module using the UDP protocol. We are handling packet dropping,  packet reordering, timeouts, failures, retransmissions, buffering, and asynchronous sending and receiving.
This implementation is used for the logic of the application.

### Brief Description of the Application
Each Peer can act as a Client or a Server, i.e. requesting images or serving images. The Peer, at startup, after log in/sign up, requests from the Directory of Service (Fixed IP) the IPs in the network, then starts communicating with them.
Every requested image has a count specifying the number of times the requesting peer can access. This number is fixed by the owner peer at the time of he serves the request.
