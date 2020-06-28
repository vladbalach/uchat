/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int query_id, int size) {
    query[0] = 17;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    return 0;
}

int mx_api_get_chats_info(t_info *info) {
    int size = 9;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, info->query_id, size);
    mx_tsend_msg(info->sock, query, size);
    return 0;
}