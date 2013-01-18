extern "C"
{
#include "system.h"
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "sc_event.h"
#include "sc_iterator.h"
#include "sc_iterator5.h"
#include "sc_stream_memory.h"
#include "identification.h"
#include "question.h"
#include "search.h"
#include "search_operations.h"
}
#include "system_pattern.h"
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldt,
            newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

sc_addr gen_input_output_arcs(){

    sc_addr node;
    sc_addr end_node;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        i++;
    }
    return node;
}

sc_addr gen_input_output_arcs_with_attr(){

    sc_addr node;
    sc_addr end_node,attr_node,arc_addr;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        attr_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        attr_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    return node;
}

sc_addr gen_input_output_arcs_with_given_attr(sc_addr attr_node){

    sc_addr node;
    sc_addr end_node,arc_addr;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    return node;
}

void gen_input_output_arcs_with_given_attr_and_given_node(sc_addr attr_node,sc_addr node){

    sc_addr end_node,arc_addr;
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
}

void test_simple_search(){
    sc_addr node=gen_input_output_arcs();
    print_element(node);
    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_output_arc(node,answer);
    print_element(answer);
    sc_memory_element_free(answer);
    answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc(node,answer);
    print_element(answer);
    search_full_semantic_neighbourhood(node,answer);
    print_element(answer);
}

void test_attr_search(){
    sc_addr node=gen_input_output_arcs_with_attr();
    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);
    print_element(answer);
}

void test_iterator5_inp(){
    sc_addr attr=sc_memory_node_new(sc_type_node);
    sc_addr node=gen_input_output_arcs_with_given_attr(attr);

    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);

    printf((sc_char*)"\n\n");

    sc_iterator5 *it=sc_iterator5_a_a_f_a_f_new(0,0,node,0,attr);
    sc_addr addr0,addr1,addr3;
    while(sc_iterator5_next(it)){
        addr0=it->results[0];
        addr1=it->results[1];
        addr3=it->results[3];
        printf((sc_char*)"\n0:%u|%u 1:%u|%u 3:%u|%u",addr0.seg,addr0.offset,addr1.seg,addr1.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void test_iterator5_outp(){
    sc_addr attr=sc_memory_node_new(sc_type_node);
    sc_addr node=gen_input_output_arcs_with_given_attr(attr);

    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);

    printf((sc_char*)"\n\n");

    sc_iterator5 *it=sc_iterator5_f_a_a_a_f_new(node,0,0,0,attr);
    sc_addr addr1,addr2,addr3;
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf((sc_char*)"\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void test_iterator5_arcs_only(){
    sc_addr attr1=sc_memory_node_new(sc_type_node);
    sc_addr attr2=sc_memory_node_new(sc_type_node);
    sc_addr node=sc_memory_node_new(sc_type_node);
    sc_addr end_node=sc_memory_node_new(sc_type_node);
    sc_addr arc_addr;

    int i=0;
    while(i<10){
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr1,arc_addr);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr2,arc_addr);
        i++;
    }
    /*i=0;
    while(i<10){
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr1,arc_addr);
        i++;
    }*/

    //sc_addr answer=sc_memory_node_new(sc_type_node);
    //search_full_semantic_neighbourhood(node,answer);

    printf((sc_char*)"\nnode1: %u|%u",node.seg,node.offset);
    printf((sc_char*)"\nnode3: %u|%u",end_node.seg,end_node.offset);
    printf((sc_char*)"\nattr: %u|%u",attr1.seg,attr1.offset);

    sc_iterator5 *it=sc_iterator5_f_a_a_a_f_new(node,0,0,0,attr1);
    sc_addr addr1,addr2,addr3;
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf((sc_char*)"\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf((sc_char*)"\n\n");

    it=sc_iterator5_a_a_f_a_f_new(0,0,end_node,0,attr1);
    while(sc_iterator5_next(it)){
        addr1=it->results[0];
        addr2=it->results[1];
        addr3=it->results[3];
        printf((sc_char*)"\n0:%u|%u 1:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf((sc_char*)"\n\n");

    it=sc_iterator5_f_a_f_a_f_new(node,0,end_node,0,attr1);
    while(sc_iterator5_next(it)){
        addr2=it->results[1];
        addr3=it->results[3];
        printf((sc_char*)"\n1:%u|%u 3:%u|%u",addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf((sc_char*)"\n\n");

    it=sc_iterator5_f_a_f_a_a_new(node,0,end_node,0,0);
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[3];
        addr3=it->results[4];
        printf((sc_char*)"\n1:%u|%u 3:%u|%u 4:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf((sc_char*)"\n\n");

    it=sc_iterator5_a_a_f_a_a_new(0,0,end_node,0,0);
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[3];
        addr3=it->results[4];
        printf((sc_char*)"\n1:%u|%u 3:%u|%u 4:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void gen_temp_identification(){
    sc_char* sys_idtf=(sc_char*)"nrel_system_identifier";
    sc_stream *stream = sc_stream_memory_new(sys_idtf, sizeof(sc_char)*strlen(sys_idtf), SC_STREAM_READ, SC_FALSE);
    sc_addr node1=sc_memory_node_new(sc_type_const|sc_type_node_norole);
    sc_addr node2=sc_memory_link_new();
    sc_memory_set_link_content(node2,stream);
    sc_stream_free(stream);
    sc_addr arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node1,node2);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,node1,arc_addr);
}

void gen_temp_identification_quasy(){
    gen_element_with_id((sc_char*)"class_quasybinary_relation",0);
}

void create_temp_question1()
{
    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,CLASS_QUESTION_FULL_SEMANTIC_NEIGHBOURHOOD,quest);
    sc_addr node=gen_input_output_arcs();
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,CLASS_QUESTION_INITIATED,quest);
}

sc_addr gen_temporary_sys_search_pattern(){
    sc_addr pattern=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node_class);
    set_element_system_id(start_node,(sc_char*)"triangle");
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start_node);

    sc_addr var_nodes[6];
    int i=0;
    for (i=0;i<6;i++){
        var_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_var);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,var_nodes[i]);
    }
    sc_addr arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[0]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[1]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[0],var_nodes[2]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[0],var_nodes[3]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[1],var_nodes[4]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[1],var_nodes[5]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);

    return pattern;
}

sc_addr gen_temporary_sys_search_pattern_mulriple_arcs(int count){
    sc_addr pattern=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node_class);
    sc_addr end_node=sc_memory_node_new(sc_type_var|sc_type_node);
    set_element_system_id(start_node,(sc_char*)"triangle");

    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,end_node);

    int i=0;
    for (i=0;i<count;i++){
        sc_addr arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    }

    return pattern;
}

sc_addr gen_temporary_sys_search_pattern_circle(){
    sc_addr pattern=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node_class);
    set_element_system_id(start_node,(sc_char*)"triangle");

    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start_node);
    sc_addr var_nodes[3];
    int i=0;
    for (i=0;i<3;i++){
        var_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_var);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,var_nodes[i]);
    }
    sc_addr arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[0]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[1]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[0],var_nodes[2]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[1],var_nodes[2]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);

    return pattern;
}

sc_addr gen_temporary_sys_search_pattern_attr(){
    sc_addr pattern=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start_node);

    set_element_system_id(start_node,(sc_char*)"triangle1");

    sc_addr first_node=sc_memory_node_new(sc_type_var|sc_type_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,first_node);

    set_element_system_id(first_node,(sc_char*)"triangle2");

    sc_addr second_node=sc_memory_node_new(sc_type_var|sc_type_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,second_node);

    set_element_system_id(second_node,(sc_char*)"triangle3");

    sc_addr arc=sc_memory_arc_new(sc_type_arc_common|sc_type_var,first_node,second_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);

    sc_addr arc1=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,arc);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc1);

    return pattern;
}

void gen_temporary_sys_search_const_data(){
    sc_addr start_node=find_element_by_id((sc_char*)"triangle");

    sc_addr const_nodes[6];
    int i=0;
    for (i=0;i<6;i++){
        const_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_var);
    }
    sc_addr arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[0]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[1]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[0],const_nodes[2]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[0],const_nodes[3]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[1],const_nodes[4]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[1],const_nodes[5]);
}


void gen_temporary_sys_search_const_data_multiple_arcs(int count){
    sc_addr start_node=find_element_by_id((sc_char*)"triangle");
    sc_addr end_node=sc_memory_node_new(sc_type_node|sc_type_const);
    int i;
    for (i=0;i<count;i++){
        sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,end_node);
    }
}

void gen_temporary_sys_search_const_data_circle(){
    sc_addr start_node=find_element_by_id((sc_char*)"triangle");

    sc_addr const_nodes[3];
    int i=0;
    for (i=0;i<3;i++){
        const_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_const);
        //const_nodes[i].seg=0;
        //const_nodes[i].offset=39+i*2;
    }

    sc_addr arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[0]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[1]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[0],const_nodes[2]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[1],const_nodes[2]);

    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[2]);
}

void gen_temporary_sys_search_const_data_attr(){  
    sc_addr start_node=find_element_by_id((sc_char*)"triangle1");
    //sc_addr first_node=find_element_by_id((sc_char*)"triangle2");
    //sc_addr second_node=find_element_by_id((sc_char*)"triangle3");

    //sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr first_node=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr second_node=sc_memory_node_new(sc_type_const|sc_type_node);

    sc_addr arc=sc_memory_arc_new(sc_type_arc_common|sc_type_const,first_node,second_node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,arc);

}

int main()
{
    sc_memory_initialize((sc_char*)"repo",(sc_char*)"test.ini");

    gen_temp_identification();
    init_identification();
    gen_temp_identification_quasy();
    init_questions();


    /*sc_event *event1 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_all_const_pos_output_arc, 0);
    sc_event *event2 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_all_const_pos_input_arc, 0);
    sc_event *event3 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_full_semantic_neighbourhood, 0);
    create_temp_question1();
    sc_event_destroy(event1);
    sc_event_destroy(event2);
    sc_event_destroy(event3);*/

    sc_addr node=gen_temporary_sys_search_pattern_circle();
    print_element(node);

    gen_temporary_sys_search_const_data_circle();

    //getch();

    GTimer *timer = 0;
    timer=g_timer_new();
    g_timer_start(timer);


    int i=0;
    sc_type_result params;
    sc_type_result_vector results;
    sc_addr_vector vars;
    sc_addr addr1,addr2;
    addr1.seg=0;addr2.seg=0;
    addr1.offset=39;addr2.offset=41;
    vars.push_back(addr1);
    vars.push_back(addr2);
    for (i=0;i<1;i++){
        system_sys_search_for_variables(node,params,vars,&results);
    }

    //system_sys_search(node);

    g_timer_stop(timer);
    printf((sc_char*)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    //sc_memory_shutdown();
    //getch();

    return 0;
}
