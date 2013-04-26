typedef struct
{
    int (*tracker_connect) (void **udata,
                            const char *host, const char *port, char *my_ip);

    int (*tracker_send) (void **udata, const void *send, int len);

    int (*tracker_recv) (void **udata, char **recv, int *rlen);

    int (*tracker_disconnect) (void **udata);
} bt_net_tracker_funcs_t;



typedef struct 
{
    void* (*add_peer)(void *udata,
        const char *peer_id,
        const int peer_id_len,
        const char *ip,
        const int ip_len,
        const int port);

    /* data to call back on */
    void* udata;
} bt_tracker_info_reader_i;


int bt_trackerclient_set_opt_int(void *bto, const char *key, const int val);