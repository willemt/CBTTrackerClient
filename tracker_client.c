
/**
 * Copyright (c) 2011, Willem-Hendrik Thiart
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. 

 * @file
 * @brief Manage connection with tracker
 * @author  Willem Thiart himself@willemthiart.com
 * @version 0.1
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>
#include <stdarg.h>

#include "url_encoder.h"
#include "tracker_client.h"
#include "tracker_client_private.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "config.h"
#include <time.h>

/* for vargs */
#include <stdarg.h>

/**
 * Initiliase the tracker client
 * @return tracker client on sucess; otherwise NULL
 */
void *trackerclient_new(
    void (*on_work_done)(void* callee, int status),
    void (*on_add_peer)(void* callee,
        char* peer_id,
        unsigned int peer_id_len,
        char* ip,
        unsigned int ip_len,
        unsigned int port),
    void* callee
    )
{
    bt_trackerclient_t *me;

    me = calloc(1, sizeof(bt_trackerclient_t));
    me->on_work_done = on_work_done;
    me->on_add_peer = on_add_peer;
    me->callee = callee;

//    if (funcs)
//        memcpy(&me->funcs,funcs,sizeof(bt_trackerclient_funcs_t));

    return me;
}

/**
 * Tell if the uri is supported or not.
 * @param uri URI to check if we support
 * @return 1 if the uri is supported, 0 otherwise
 */
int trackerclient_supports_uri(void* _me __attribute__((__unused__)), const char* uri)
{
    if (0 == strncmp(uri,"udp://",6))
    {
        // TODO
        return 0;
    }
    else if (0 == strncmp(uri,"http://",7))
    {
        return 1;
    }
    else if (0 == strncmp(uri,"dht://",6))
    {
        // TODO
        return 0;
    }

    return 0;
}

/**
 * Connect to the URI.
 * @param uri URI to connnect to
 * @return 1 if successful, 0 otherwise
 */
int trackerclient_connect_to_uri(void* me_, const char* uri)
{
    bt_trackerclient_t* me = me_;

    if (0 == trackerclient_supports_uri(me_,uri))
    {
        return 0;
    }

    if (0 == strncmp(uri,"udp://",6))
    {
        // TODO
        return 0;
    }
    else if (0 == strncmp(uri,"http://",7))
    {
        me->uri = strdup(uri);
        thttp_connect(me,uri+7);
        return 1;
    }
    else if (0 == strncmp(uri,"dht://",6))
    {
        // TODO
        return 0;
    }

    return 0;
}

/**
 * Release all memory used by the tracker client
 * @return 1 if successful; 0 otherwise
 * @todo add destructors
 */
int trackerclient_release(void *bto)
{
    free(bto);
    return 1;
}

/**
 * Set configuration of tracker client
 * @param me_ Tracker client
 * @param cfg Configuration to reference/use
 */
void trackerclient_set_cfg(
        void *me_,
        void *cfg
        )
{
    bt_trackerclient_t* me = me_;

    assert(cfg);
    me->cfg = cfg;
}

/**
 * Receive this much data on this step.
 * @param me_ Tracker client
 * @param buf Buffer to dispatch events from
 * @param len Length of buffer
 */
void trackerclient_dispatch_from_buffer(
        void *me_,
        const unsigned char* buf,
        unsigned int len)
{
    bt_trackerclient_t* me = me_;

    thttp_dispatch_from_buffer(me, buf, len);
}

#if 0
void trackerclient_periodic(void *bto __attribute__((__unused__)))
{
    bt_trackerclient_t *self = bto;
    time_t seconds;

    seconds = time(NULL);

    /*  perform tracker request to get new peers */
    if (self->last_tracker_request + self->cfg.tracker_scrape_interval < seconds)
    {
        self->last_tracker_request = seconds;
        __get_http_tracker_request(self);
    }
}
#endif

