/*
 * SPDX-FileCopyrightText: 2019-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "esp_tls.h"
#include "esp_tls_private.h"

/**
 * Internal Callback API for mbedtls_ssl_read
 */
ssize_t esp_mbedtls_read(esp_tls_t *tls, char *data, size_t datalen);

/**
 * Internal callback API for mbedtls_ssl_write
 */
ssize_t esp_mbedtls_write(esp_tls_t *tls, const char *data, size_t datalen);

/**
 * Internal Callback for mbedtls_handshake
 */
int esp_mbedtls_handshake(esp_tls_t *tls, const esp_tls_cfg_t *cfg);

/**
 * Internal Callback for mbedtls_cleanup , frees up all the memory used by mbedtls
 */
void esp_mbedtls_cleanup(esp_tls_t *tls);

/**
 * Internal Callback for Certificate verification for mbedtls
 */
void esp_mbedtls_verify_certificate(esp_tls_t *tls);

/**
 * Internal Callback for deleting the mbedtls connection
 */
void esp_mbedtls_conn_delete(esp_tls_t *tls);

/**
 * Internal Callback for mbedtls_get_bytes_avail
 */
ssize_t esp_mbedtls_get_bytes_avail(esp_tls_t *tls);

/**
 * Internal Callback for creating ssl handle for mbedtls
 */
esp_err_t esp_create_mbedtls_handle(const char *hostname, size_t hostlen, const void *cfg, esp_tls_t *tls, void* server_params);

/**
 * mbedTLS function for Initializing socket wrappers
 */
static inline void esp_mbedtls_net_init(esp_tls_t *tls)
{
    mbedtls_net_init(&tls->server_fd);
}

/**
 * Return ssl context for mbedTLS stack
 */
void *esp_mbedtls_get_ssl_context(esp_tls_t *tls);


/**
 * Internal Callback for mbedtls_server_session_create
 *
 * /note :- The function can only be used with mbedtls ssl library
 */
int esp_mbedtls_server_session_create(esp_tls_cfg_server_t *cfg, int sockfd, esp_tls_t *tls);

/**
 * Initialization part of internal callback for mbedtls_server_session_create
 */
esp_err_t esp_mbedtls_server_session_init(esp_tls_cfg_server_t *cfg, int sockfd, esp_tls_t *tls);

/**
 * Asynchronous continue of internal callback for mbedtls_server_session_create,
 * to be called in a loop by the user until it returns 0,
 * ESP_TLS_ERR_SSL_WANT_READ or ESP_TLS_ERR_SSL_WANT_WRITE.
 */
int esp_mbedtls_server_session_continue_async(esp_tls_t *tls);

/**
 * Internal Callback for mbedtls_server_session_delete
 *
 * /note :- The function can only be used with mbedtls ssl library
 */
void esp_mbedtls_server_session_delete(esp_tls_t *tls);

#ifdef CONFIG_ESP_TLS_SERVER_SESSION_TICKETS
/**
 * Internal function to setup server side session ticket context
 *
 * /note :- The function can only be used with mbedtls ssl library
 */
esp_err_t esp_mbedtls_server_session_ticket_ctx_init(esp_tls_server_session_ticket_ctx_t *cfg);

/**
 * Internal function to free server side session ticket context
 *
 * /note :- The function can only be used with mbedtls ssl library
 */
void esp_mbedtls_server_session_ticket_ctx_free(esp_tls_server_session_ticket_ctx_t *cfg);
#endif

/**
 * Internal Callback for set_client_config_function
 */
esp_err_t set_client_config(const char *hostname, size_t hostlen, esp_tls_cfg_t *cfg, esp_tls_t *tls);

#ifdef CONFIG_ESP_TLS_CLIENT_SESSION_TICKETS
/**
 * Internal Callback for mbedtls_get_client_session
 */
esp_tls_client_session_t *esp_mbedtls_get_client_session(esp_tls_t *tls);

/**
 * Internal Callback for mbedtls_free_client_session
 */
void esp_mbedtls_free_client_session(esp_tls_client_session_t *client_session);
#endif

/**
 * Internal Callback for mbedtls_init_global_ca_store
 */
esp_err_t esp_mbedtls_init_global_ca_store(void);

/**
 * Callback function for setting global CA store data for TLS/SSL using mbedtls
 */
esp_err_t esp_mbedtls_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes);

/**
 * Internal Callback for esp_tls_global_ca_store
 */
mbedtls_x509_crt *esp_mbedtls_get_global_ca_store(void);

/**
 * Callback function for freeing global ca store for TLS/SSL using mbedtls
 */
void esp_mbedtls_free_global_ca_store(void);

/**
 * Internal Callback for esp_tls_get_ciphersuites_list
 */
const int *esp_mbedtls_get_ciphersuites_list(void);
