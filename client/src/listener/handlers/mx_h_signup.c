#include "client.h"

static t_user_info* get_user(t_info* info) {
    t_user_info* uinfo = malloc(sizeof(t_user_info));
    uinfo->avatar = '1';
    uinfo->frst_name = 0; 
    uinfo->nickname = 0;
    uinfo->scnd_name = 0;
    return uinfo;
}

int mx_h_signup(char *response, t_info *info) {
    if (response[9] == (char)200) {
        info->user_info = get_user(info);
    }
    else {
        // NOT REGISTERED
        printf("SIGNIN ERR STATUS = %d\n", response[9]);
    }
    return 0;
}
