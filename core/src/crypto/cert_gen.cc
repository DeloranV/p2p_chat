#include "crypto/cert_gen.h"
#include <fstream>

namespace crypto {
  inline bool keys_exist() {
    std::ifstream key("key.pem");
    std::ifstream crt("cert.pem");
    bool exist = key.good() && crt.good();

    key.close();
    crt.close();
    return exist;
  }

  void create_private_key() {
    if (keys_exist()) return;

    EVP_PKEY* pkey;
    pkey = EVP_PKEY_new();

    RSA* rsa;
    rsa = RSA_generate_key(
      2048,
      RSA_F4,
      NULL,
      NULL
    );
    EVP_PKEY_assign_RSA(pkey, rsa);

    X509* x509;
    x509 = X509_new();

    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);

    X509_set_pubkey(x509, pkey);

    X509_NAME* name;
    name = X509_get_subject_name(x509);

    X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC,
                           (unsigned char *)"CA", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC,
                               (unsigned char *)"MyCompany Inc.", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC,
                               (unsigned char *)"localhost", -1, -1, 0);

    X509_set_issuer_name(x509, name);

    X509_sign(x509, pkey, EVP_sha1());

    FILE* f;
    f = fopen("key.pem", "wb");
    PEM_write_PrivateKey(
      f,
      pkey,
      NULL,
      NULL,
      10,
      NULL,
      NULL
    );
    fclose(f);

    FILE* c;
    c = fopen("cert.pem", "wb");
    PEM_write_X509(
      f,
      x509
    );
    fclose(c);

    X509_free(x509);
    EVP_PKEY_free(pkey);
  }
}