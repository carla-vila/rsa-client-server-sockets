#ifndef SOCKET_COMMUNICATION_H
#define SOCKET_COMMUNICATION_H

#include <stdint.h> // Include for uint64_t type

int connect_to_server(const char *server_ip, int port);
void send_data(int socket_fd, const char *data);
void close_connection(int socket_fd);
void send_encrypted_data(uint64_t z[20]); // Updated function signature to accept an array of uint64_t

#endif /* SOCKET_COMMUNICATION_H */
