#include "sock.h"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

// const char *node,     // e.g. "www.example.com" or IP
//                 const char *service,  // e.g. "http" or port number
//                 const struct addrinfo *hints,
//                 struct addrinfo **res
int example_fn() {
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;  // list with result

    memset(&hints, 0, sizeof hints);  // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;      // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;      // fill in my IP for me

    const char *url = "id.staging.layers.digital";

    printf("Calling getaddrinfo for %s\n", url);

    if ((status = getaddrinfo(url, "3490", &hints, &servinfo)) != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // servinfo now points to a linked list of 1 or more struct addrinfos
    // struct addrinfo {
    //     int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    //     int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    //     int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    //     int              ai_protocol;  // use 0 for "any"
    //     size_t           ai_addrlen;   // size of ai_addr in bytes
    //     struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    //     char            *ai_canonname; // full canonical hostname
    // }
    struct addrinfo *p;
    int i = 0;
    char ipstr[INET6_ADDRSTRLEN];
    for (p = servinfo; p != NULL && i < 100; p = p->ai_next, i++) {
        void *addr;
        char *ipver;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) {  // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {  // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(servinfo);  // free the linked-list
    return status;
}