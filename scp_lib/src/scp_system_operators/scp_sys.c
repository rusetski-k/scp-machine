/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2013 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "../scp_types.h"
#include "../scp_utils.h"
#include "scp_sys_search.h"
#include "scp_sys_gen.h"
#include "sc_memory_headers.h"

scp_result scp_sys_search(scp_operand *param1, scp_operand *param2, scp_operand_pair *parameters, sc_uint32 param_count, scp_operand *param4, scp_bool full_only)
{
    scp_bool flag2;
    sc_uint32 i;
    if (param1->param_type != SCP_FIXED)
    {
        return print_error("scp_sys_search", "Parameter 1 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error("scp_sys_search", "Parameter 1 has modifier FIXED, but has not value");
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("scp_sys_search", "Parameter 2 has modifier FIXED, but has not value");
        }
    }
    else
    {
        flag2 = SCP_TRUE;
    }

    for (i = 0; i < param_count; i++)
    {
        if (parameters[i].operand1->param_type == SCP_ASSIGN || parameters[i].operand2->param_type == SCP_ASSIGN)
        {
            return print_error("scp_sys_search", "All elements of parameter set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(parameters[i].operand1->addr) || SC_FALSE == sc_memory_is_element(parameters[i].operand2->addr))
        {
            return print_error("scp_sys_search", "All elements of parameter set must have value");
        }
    }

    if (flag2 == SCP_TRUE)
    {
        param2->addr = sc_memory_node_new(scp_type_const);
    }
    return sys_search(param1, param2, parameters, param_count, param4, full_only);
}

scp_result scp_sys_search_for_variables(scp_operand *param1, scp_operand_pair *variables, sc_uint32 var_count, scp_operand_pair *parameters, sc_uint32 param_count, scp_operand *param4)
{
    sc_uint32 i;
    if (param1->param_type != SCP_FIXED)
    {
        return print_error("scp_sys_search_for_variables", "Parameter 1 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error("scp_sys_search_for_variables", "Parameter 1 has modifier FIXED, but has not value");
    }
    for (i = 0; i < param_count; i++)
    {
        if (parameters[i].operand1->param_type == SCP_ASSIGN || parameters[i].operand2->param_type == SCP_ASSIGN)
        {
            return print_error("scp_sys_search_for_variables", "All elements of parameter set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(parameters[i].operand1->addr) || SC_FALSE == sc_memory_is_element(parameters[i].operand2->addr))
        {
            return print_error("scp_sys_search_for_variables", "All elements of parameter set must have value");
        }
    }
    for (i = 0; i < var_count; i++)
    {
        if (variables[i].operand1->param_type == SCP_ASSIGN)
        {
            return print_error("scp_sys_search_for_variables", "All variables of variable set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(variables[i].operand1->addr))
        {
            return print_error("scp_sys_search_for_variables", "All variables of variable set must have value");
        }
        if (variables[i].operand2->param_type == SCP_FIXED)
        {
            if (variables[i].operand2->set == SCP_TRUE)
            {
                if (SC_FALSE == sc_memory_is_element(variables[i].operand2->addr))
                {
                    return print_error("scp_sys_search_for_variables", "Variable value of variables set marked as FIXED SET but has no value");
                }
            }
            else
            {
                return print_error("scp_sys_search_for_variables", "Variable value of variables set marked as FIXED but not marked as SET");
            }
        }
    }
    for (i = 0; i < var_count; i++)
    {
        if (variables[i].operand2->param_type == SCP_ASSIGN && variables[i].operand2->set == SCP_TRUE)
        {
            variables[i].operand2->addr = sc_memory_node_new(scp_type_const);
        }
    }
    return sys_search_for_variables(param1, variables, var_count, parameters, param_count, param4);
}

scp_result scp_sys_gen(scp_operand *param1, scp_operand *param2, scp_operand_pair *parameters, sc_uint32 param_count, scp_operand *param4)
{
    scp_bool flag2;
    sc_uint32 i;
    if (param1->param_type != SCP_FIXED)
    {
        return print_error("sys_gen", "Parameter 1 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error("sys_gen", "Parameter 1 has modifier FIXED, but has not value");
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("sys_gen", "Parameter 2 has modifier FIXED, but has not value");
        }
    }
    else
    {
        flag2 = SCP_TRUE;
    }

    for (i = 0; i < param_count; i++)
    {
        if (parameters[i].operand1->param_type == SCP_ASSIGN || parameters[i].operand2->param_type == SCP_ASSIGN)
        {
            return print_error("sys_gen", "All elements of parameter set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(parameters[i].operand1->addr) || SC_FALSE == sc_memory_is_element(parameters[i].operand2->addr))
        {
            return print_error("sys_gen", "All elements of parameter set must have value");
        }
    }

    if (flag2 == SCP_TRUE)
    {
        param2->addr = sc_memory_node_new(scp_type_const);
    }
    return sys_gen(param1, param2, parameters, param_count, param4);
}

scp_result scp_sys_gen_for_variables(scp_operand *param1, scp_operand_pair *variables, sc_uint32 var_count, scp_operand_pair *parameters, sc_uint32 param_count, scp_operand *param4)
{
    sc_uint32 i;
    if (param1->param_type != SCP_FIXED)
    {
        return print_error("sys_gen_for_variables", "Parameter 1 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error("sys_gen_for_variables", "Parameter 1 has modifier FIXED, but has not value");
    }
    for (i = 0; i < param_count; i++)
    {
        if (parameters[i].operand1->param_type == SCP_ASSIGN || parameters[i].operand2->param_type == SCP_ASSIGN)
        {
            return print_error("sys_gen_for_variables", "All elements of parameter set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(parameters[i].operand1->addr) || SC_FALSE == sc_memory_is_element(parameters[i].operand2->addr))
        {
            return print_error("sys_gen_for_variables", "All elements of parameter set must have value");
        }
    }
    for (i = 0; i < var_count; i++)
    {
        if (variables[i].operand1->param_type == SCP_ASSIGN)
        {
            return print_error("sys_gen_for_variables", "All variables of variable set must have FIXED modifier");
        }
        if (SC_FALSE == sc_memory_is_element(variables[i].operand1->addr))
        {
            return print_error("sys_gen_for_variables", "All variables of variable set must have value");
        }
        if (variables[i].operand2->param_type == SCP_FIXED)
        {
            return print_error("sys_gen_for_variables", "All variables values must have ASSIGN modifier");
        }
    }
    for (i = 0; i < var_count; i++)
    {
        if (variables[i].operand2->param_type == SCP_ASSIGN && variables[i].operand2->set == SCP_TRUE)
        {
            variables[i].operand2->addr = sc_memory_node_new(scp_type_const);
        }
    }
    return sys_gen_for_variables(param1, variables, var_count, parameters, param_count, param4);
}