#include "server.h"
#include "defines.h"


static char *create_response(char *id_msg) {
    char *respons = malloc(sizeof(char) * 20);

    memset(respons, 0, 20);
    respons[0] = 4;
    respons[5] = 20;
    sprintf(&respons[9], "%s", id_msg);
    return respons;
}

static int delete_msg_to_db(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int a = 0;

    sprintf(sql, "update msg set msg_status='4', msg_send_time=datetime('now') "
            "where msg_id='%s';", &user->buff[20]);
    a = mx_do_query(sql, 0, 0,server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}

char *mx_delete_msg(t_server *server_info, t_server_users *user) {
    char sql[100];
    char *response = 0;

    if (mx_check_number(&user->buff[9], 11) == 0
        || mx_check_number(&user->buff[20], 11) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_FUNC);
    if (mx_check_id_message_in_user(&user->buff[9], &user->buff[20],
                                    server_info, user) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_RIGHT);
    if (delete_msg_to_db(server_info, user))
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MQ_QS_ERR_SQL);
    sprintf(sql, "select cou_usr_id from cou where cou_char_id = "
            "%s;", &user->buff[20]);
    response = create_response(&user->buff[9]);
    mx_send_response_user(server_info, response, sql);
    free(response);
    return 0;
}