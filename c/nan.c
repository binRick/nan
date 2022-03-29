#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/********/
#include "../../reflect/src/metaref.h"
/********/
#include "../../reflect/src/reflect.c"
/********/
#include "../../reflect/src/stp_print.c"
/********/
#include "../../log/log.c"
/********/


/**********************************************/
REFLECTIVE(item1,
           FIELD(int, id);
           FIELD(int, id1);
           FIELD(char *, name);
           );
REFLECTIVE(item,
           FIELD(int, id);
           FIELD(char *, name);
           );
REFLECTIVE(account_t,
           FIELD(int, id);
           FIELD(char *, name);
           FIELD(item1, item1);
           FIELD(item, item);
           );
/**********************************************/
stp_print_begin(item1, 3) {
  stp_print_field_int(id);
  stp_print_field_int(id1);
  stp_print_field_string(name);
  stp_print_end();
}

stp_print_begin(item, 2) {
  stp_print_field_int(id);
  stp_print_field_string(name);
  stp_print_end();
}

stp_print_begin(account_t, 4) {
  stp_print_field_int(id);
  stp_print_field_string(name);
  stp_print_field_struct(item1, item1);
  stp_print_field_struct(item, item);
  stp_print_end();
}

/**********************************************/
#define fmt1    "%20s"
#define fmt2    " is "
#define fmt3    "'%s'\n"

#define type_fmt(expr)                                                          \
  (_Generic((expr),                                                             \
            char *: "%s",                                                       \
            char : "%c", unsigned char : "%uc", signed char : "%c",             \
            short : "%s", unsigned short : "%us",                               \
            int : "%d", unsigned int : "%d",                                    \
            long : "%zu", unsigned long : "%lu",                                \
            long long : "long long", unsigned long long : "unsigned long long", \
            float : "%f",                                                       \
            double : "double",                                                  \
            long double : "long double",                                        \
            void *: "void*",                                                    \
          default: "?"))

#define type_size(expr) \
  (_Generic((expr),     \
          default: sizeof(expr))

#define type_class(expr)                                                                 \
  (_Generic((expr),                                                                      \
            char *: "string",                                                            \
            char **: "string array",                                                     \
            char : "char", unsigned char : "unsigned char", signed char : "signed char", \
            short : "short", unsigned short : "unsigned short",                          \
            int : "number", unsigned int : "number",                                     \
            long : "long", unsigned long : "unsigned long",                              \
            long long : "long long", unsigned long long : "unsigned long long",          \
            float : "float",                                                             \
            double : "double",                                                           \
            long double : "long double",                                                 \
            void *: "void*",                                                             \
          default: "?"))

#define type_name(expr)                                                                  \
  (_Generic((expr),                                                                      \
            char *: "char*",                                                             \
            char **: "char**",                                                           \
            char : "char", unsigned char : "unsigned char", signed char : "signed char", \
            short : "short", unsigned short : "unsigned short",                          \
            int : "int", unsigned int : "unsigned int",                                  \
            long : "long", unsigned long : "unsigned long",                              \
            long long : "long long", unsigned long long : "unsigned long long",          \
            float : "float",                                                             \
            double : "double",                                                           \
            long double : "long double",                                                 \
            void *: "void*",                                                             \
          default: "?"))
/**********************************************/
#define var(expr)                                                             \
  print(                                                                      \
    AC_RESETALL AC_YELLOW "Variable" AC_RESETALL, METAREF_VALUE_TO_STR(expr), \
    AC_RESETALL AC_YELLOW "has class" AC_RESETALL, type_class(expr),          \
    "| size", sizeof(expr), "b",                                              \
    "| type", METAREF_GENERIC_TYPE_STR(expr),                                 \
    "| formatter", METAREF_GENERIC_FORMAT_SPECIFIER(expr),                    \
    "| value:", expr                                                          \
    )


/**********************************************/
void print_data(account_t *ptr, int level){
  char msg[1024];

  stp_snprintf(account_t, msg, sizeof(msg), ptr, "Account", level);
  printf("---\n%s---\n", msg);
}


/**********************************************/
int dev1() {
  int           i1   = 25;
  long unsigned i2   = 239999;
  char          *s   = "aaa111111111";
  account_t     acc2 = {
    .id    = 25,
    .name  = "yyyyyyyyy",
    .item  = { .id = 24, .name = "c" },
    .item1 = { .id = 23, .id1  = 100, .name = "b"},
  };

  var(i1);
  var(i2);
  var(s);
  var(acc2.id);
  var(acc2.name);
  var(acc2.item1.id);
  var(acc2.item1.name);
  var(acc2.item);
  var(acc2.item1.name);
  print_data(&(acc2), 1);
}


void reflect5(){
  char *s;
  int  i = 23;

  s = METAREF_VALUE_TO_STR(i);
  log_debug("METAREF_VALUE_TO_STR(i):%s", s);
  log_debug("METAREF_GENERIC_TYPE_STR(i):%s", METAREF_GENERIC_TYPE_STR(i));
  log_debug("METAREF_GENERIC_TYPE_STR(s):%s", METAREF_GENERIC_TYPE_STR(s));
  log_debug("METAREF_GENERIC_FORMAT_SPECIFIER(s):%s", METAREF_GENERIC_FORMAT_SPECIFIER(s));
}


void reflect4(){
  int  i     = 23;
  char s[10] = "abc";
  char *s1   = "def";

  log_debug("typename:%s", type_name(i));
  log_debug("typename:%s", type_name(s));
  log_debug("typename:%s", type_name(s1));

  log_debug("fmt:%s", type_fmt(i));
  log_debug("fmt:%s", type_fmt(s));
  log_debug("fmt:%s", type_fmt(s1));

  log_debug("typeid:%d", __print_typeid(i));
  log_debug("typeid:%d", __print_typeid(s));
  log_debug("typeid:%d", __print_typeid(s1));
}


void reflect3(){
  account_t acc2 = {
    .id    = 25,
    .name  = "yyyyyyyyy",
    .item  = { .id = 23, .name  = "b" },
    .item1 = { .id = 24, .name  = "c" },
  };

  print_data(&acc2, 1);
}


void reflect2(){
  account_t *acc1 = malloc(sizeof(account_t));

  acc1->id   = 10;
  acc1->name = "Bob";

  acc1->item.id   = 100;
  acc1->item.name = "a";

  acc1->item1.id   = 2;
  acc1->item1.name = "b";

  print_data(acc1, 1);
}


void reflect1(){
  field *acc1_fields = account_t_get_fields();

  printf("Structure has %d fields\n", account_t_get_num_fields());
  for (int i = 0; i < account_t_get_num_fields(); ++i) {
    print("variable named", acc1_fields[i].name, " has class ", type_class(123), " and size of ", acc1_fields[i].size, " bytes");
    printf(
      AC_RESETALL AC_RED AC_BOLD  " - "
      AC_RESETALL AC_REVERSED AC_BLUE AC_BOLD  "%s"
      AC_RESETALL "  \t" AC_RESETALL
      AC_RESETALL AC_YELLOW "(%s)" AC_RESETALL
      AC_RESETALL "  \t" AC_RESETALL
      AC_RESETALL "\n"
      "",
      acc1_fields[i].name,
      bytes_to_string(acc1_fields[i].size)
      );
  }
  printf("\n");
  log_debug("fq:%d", NUM_FIELDS(account_t));
  log_debug("t1:%d", account_t_t1());
  printf("\n");
}


int dev() {
  char *st = "abc123";  void *sv = (void *)st; float nan = NAN;  size_t s; ptrdiff_t p; intmax_t i; int ai[3] = { 0 };

  return(fprintf(stderr,
                 ""
                 AC_RESETALL AC_YELLOW fmt1 AC_RESETALL
                 AC_MAGENTA fmt2 AC_RESETALL
                 AC_RED fmt3 AC_RESETALL

                 "\n",
                 "size_t", type_name(s),
                 "ptrdiff_t", type_name(p),
                 "intmax_t", type_name(i),

                 "character constant", type_name('0'),

                 "0x7FFFFFFF", type_name(0x7FFFFFFF),
                 "0xFFFFFFFF", type_name(0xFFFFFFFF),

                 "nan", type_name(nan),

                 "char *st", type_name(st),
                 "(void*)sv", type_name(sv),

                 "array of int", type_name(ai)

                 ));
}


/**********************************************/
int main() {
  dev();
  reflect1();
  reflect2();
  reflect3();
  reflect4();
  reflect5();
  dev1();
  return(0);
}
