#include "client.h"
#include "defines.h"

int mx_handle_response(t_info *info, char *response) {
    int (*handlers[])(char *, t_info *) = {
        mx_h_signup, // 0
        mx_h_signin, // 1
        mx_h_send_msg, // 2
        mx_h_edit_msg, // 3
        mx_h_delete_msg, // 4
        mx_h_send_file, // 5
        mx_h_get_user_info, // 6
        mx_h_get_chat_users, // 7
        mx_h_get_msgs_time, // 8
        mx_h_show_users, // 9
        mx_h_get_chat_info, // 10
        mx_h_get_file, // 11
        mx_h_authenticate, // 12
        mx_h_join_chat, // 13
        mx_h_create_chat, // 14
        mx_h_create_dialog, // 15
        mx_h_leave_chat // 16
        };

    if (response[0] > MX_COUNT_API) {
        fprintf(stderr, "Error API number: %d\n", response[0]);
        return -1;
    }
    int (*foo)(char *, t_info *) =  (*handlers[response[0]]);
    return foo(response, info);
}