#define IDLE_TIMEOUT_MS  3000
#define RETRY_TIMEOUT 3000

// Include libraries
#include <Ethernet.h>

class WebSocketClient {
public:
  typedef void (*OnMessage)(WebSocketClient client, char* message);
  typedef void (*OnOpen)(WebSocketClient client);
  typedef void (*OnClose)(WebSocketClient client, int code, char* message);
  typedef void (*OnError)(WebSocketClient client, char* message);
  WebSocketClient(char * protocol);

  void connect(uint32_t ip, int port);
  void connect(char * server, int port);

  void monitor(uint32_t ip, int port);
  void monitor(char * server, int port);

  void sendHandshake();
  void readHandshake();

  void processMonitor();
 
  byte nextByte();
  void onOpen(OnOpen function);
  void onClose(OnClose function);
  void onMessage(OnMessage function);
  void onError(OnError function);
  bool send(char* message);
  bool sendMessage(char * message);
  void generateHash(char* buffer, size_t bufferlen);
  size_t base64Encode(byte* src, size_t srclength, char* target, size_t targetsize);
 
private:

  EthernetClient _client;

  char * _protocol;
  char * _server;
  uint32_t _ip;
  String monitor_answer;
  char* _packet;
  OnOpen _onOpen;
  OnClose _onClose;
  OnMessage _onMessage;
  OnError _onError;
  unsigned int _packetLength;
  byte _opCode;
  bool _canConnect;
  bool _reconnecting;
  unsigned long _retryTimeout;
};

const char b64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";