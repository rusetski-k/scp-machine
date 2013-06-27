#include "scp_functions.h"
#include "scp_types.h"
#include <stdio.h>

int main(void)
{
    scp_lib_init((sc_char *)"repo", (sc_char *)"test.ini");

    scp_operand param1;
    param1.element_type = scp_type_node | scp_type_const;
    param1.param_type = SCP_ASSIGN;

    genEl(&param1);

    param1.param_type = SCP_FIXED;

    printEl(&param1);

    scp_operand param2;
    param2.element_type = scp_type_const;
    param2.param_type = SCP_ASSIGN;

    scp_operand param3;
    param3.element_type = scp_type_node | scp_type_const;
    param3.param_type = SCP_ASSIGN;

    scp_operand param4;
    param4.element_type = scp_type_const;
    param4.param_type = SCP_ASSIGN;

    scp_operand param5;
    param5.element_type = scp_type_node | scp_type_const;
    param5.param_type = SCP_ASSIGN;

    genElStr5(&param1, &param2, &param3, &param4, &param5);

    printEl(&param1);

    param1.param_type = SCP_FIXED;
    param2.param_type = SCP_ASSIGN;
    param3.param_type = SCP_ASSIGN;
    param4.param_type = SCP_ASSIGN;
    param5.param_type = SCP_FIXED;
    scp_result res = searchElStr5(&param1, &param2, &param3, &param4, &param5);

    if (res == SCP_TRUE)
    {
        printf("TRUE\n");
    }
    if (res == SCP_FALSE)
    {
        printf("FALSE\n");
    }
    if (res == SCP_ERROR)
    {
        printf("ERROR\n");
    }

    if (param1.param_type == SCP_ASSIGN)
    {
        printEl(&param1);
    }
    if (param2.param_type == SCP_ASSIGN)
    {
        printEl(&param2);
    }
    if (param3.param_type == SCP_ASSIGN)
    {
        printEl(&param3);
    }
    if (param4.param_type == SCP_ASSIGN)
    {
        printEl(&param4);
    }
    if (param5.param_type == SCP_ASSIGN)
    {
        printEl(&param5);
    }

    param1.erase=SCP_ERASE_TRUE;
    param1.param_type=SCP_FIXED;
    eraseEl(&param1);

    //scp_lib_shutdown();
    return 0;
}
