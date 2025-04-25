#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
 
int is_valid_elbrus(const char *value) {
    const char *valid[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};
    for (int i = 0; i < sizeof(valid)/sizeof(valid[0]); i++) {
        if (strcmp(value, valid[i]) == 0) return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    int opt;
    int option_index = 0;
    int m_flag = 0, c_flag = 0, s_flag = 0, t_flag = 0;
    char *elbrus_values[10];
    int elbrus_count = 0;

    char *non_opts[argc];
    int non_opt_count = 0;

    static struct option long_options[] = {
        {"elbrus", required_argument, 0, 0},
        {0, 0, 0, 0}
    };

    optind = 1;

    while ((opt = getopt_long(argc, argv, "mcst", long_options, &option_index)) != -1) {
        switch (opt) {
            case 0: // длинные опции (в нашем случае только --elbrus)
                if (strcmp("elbrus", long_options[option_index].name) == 0) {
                    if (!is_valid_elbrus(optarg)) {
                        printf("Options are incorrect.\nInvalid elbrus option: %s\n", optarg);
                        return 1;
                    }
                    elbrus_values[elbrus_count++] = optarg;
                }
                break;
            case 'm':
                m_flag = 1;
                break;
            case 'c':
                c_flag = 1;
                break;
            case 's':
                s_flag = 1;
                break;
            case 't':
                t_flag = 1;
                break;
            case '?': // getopt автоматически напечатает сообщение об ошибке
                printf("Options are incorrect.\nInvalid option: -%c\n", optopt);
                return 1;
            default:
                printf("Options are incorrect.\nUnknown error.\n");
                return 1;
        }
    }
    
}

