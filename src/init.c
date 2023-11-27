#include "jssl.h" 
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <stdio.h>

/* Loading the FIPS provider is often not enough to get openssl's full functionality.
   We also should load the base provider. The base provider does not provide for
   any crypto functionality, but has other functionality like the encoders for example.

   These two comments saved my day:
   https://github.com/openssl/openssl/issues/13773#issuecomment-756225529
   https://github.com/openssl/openssl/issues/13773#issuecomment-756233808
*/ 

OSSL_LIB_CTX* load_openssl_provider(const char *name, const char* conf_file_path) {
    OSSL_LIB_CTX *libctx = OSSL_LIB_CTX_new();
    if (!OSSL_LIB_CTX_load_config(libctx, conf_file_path)) {
        ERR_print_errors_fp(stderr);
    }

    OSSL_PROVIDER *prov = OSSL_PROVIDER_load(NULL, name);
    if (NULL == prov) {
        fprintf(stderr, "Failed to load the %s provider:\n", name);
        ERR_print_errors_fp(stderr);
    }
    
    return libctx;
}

OSSL_LIB_CTX* load_openssl_fips_provider(const char* conf_file_path) {
    load_openssl_provider("fips", conf_file_path);
}

OSSL_LIB_CTX* load_openssl_base_provider(const char* conf_file_path) {
    load_openssl_provider("base", conf_file_path);
}
