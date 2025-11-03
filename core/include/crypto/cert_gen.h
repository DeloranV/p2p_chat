#ifndef CHAT_APP_CERT_GEN_H
#define CHAT_APP_CERT_GEN_H

#include <openssl/pem.h>
#include <openssl/x509v3.h>
#include <openssl/rsa.h>

namespace crypto {
  void create_private_key();
}

#endif //CHAT_APP_CERT_GEN_H