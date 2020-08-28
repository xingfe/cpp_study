#include <zmq.hpp>
#include <string>
#include <iostream>

class PeerNode{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    PeerNode(int i){
        int port = 5555+id;
        socket.connect ("tcp://localhost:"+string(port));
    }
    void send_request(zmq::message_t & request ){
        socket.send (request);
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received World " << handle_reply(reply) << std::endl;
    }

};


class Node{
    map<int, PeerNode> peer;
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);

    Node(int id){
        int port = 5555+id;
        socket.bind ("tcp://*:"+string(port));
        for(int i=0; i< size; i++){
            if (i== id){
                continue;
            }
            peers[i] = PeerNode(i);
        }
    }

    void recv_request(zmq::message_t & request){
        socket.recv (&request);
        auto reply = make_response(request);
        socket.send (reply);
    }
    void start(){
        while(true){
            zmq::message_t request;
            recv_request(request);
        }
    }

};

int main (){
    //  Prepare our context and socket
    Node node(1));
    node.start();
    return 0;
}
