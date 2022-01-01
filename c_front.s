
annotation:"//".*$

string:\"[("\".)^\"]*\"

?:[@annotation@\s+]

?segmentation<:\s+

integer:[0-9]+

label:[_a-zA-Z][_a-zA-Z0-9]*

colon:":"

semicolon:";"

oper_comma:","

oper_as:"="

oper_inc:"++"

oper_dec:"--"

oper_dot:"."

round_left:"("

round_right:")"

square_left:"["

square_right:"]"

block_left:"{"

block_right:"}"

round:@round_left@@expression@@round_right@

variable_def:(@arbitrarily_type@@segmentation@@variable@(@oper_as@@expression@)?)#VariableDef#

statement:[@return_s@@goto@@proc_call@@variable_def@@expression@]

expression:[(@oper_one@@variable@)(@variable@[@oper_inc@@oper_dec@])(@element@(@oper_two@@element@)*)]

element:[@round@@proc_call@@string@@variable@@numeric@@integer@@address_s@@sizeof_s@]

sizeof:"sizeof"

sizeof_s:[(@sizeof@@round@)(@sizeof@@element@)]

oper_two:[@oper_comma@@oper_assgin@@oper_logic_or@
@oper_logic_and@@oper_bit_or@@oper_bit_xor@@oper_bit_and@
@oper_equal@@oper_rela@@oper_mov@@oper_add_sub@@oper_mul_div@]

oper_assgin:[@oper_as@"+=""-=""*=""/=""%=""&=""^=""|=""<<="">>="]

oper_logic_or:"||"

oper_logic_and:"&&"

oper_bit_or:"|"

oper_bit_xor:"^"

oper_bit_and:"&"

oper_equal:["==""!="]

oper_rela:["<""<="">"">="]

oper_mov:["<<"">>"]

oper_add_sub:["+""-"]

oper_mul_div:["*""/""%"]

oper_one:["-"@oper_inc@@oper_dec@"!""~""+""-""*""&"]

type_cast:@round_left@@label@@round_right@

oper_suffix:[@oper_dot@"->"]

numeric:@integer@(@oper_dot@@integer@)?

variable:@pointer@*@label@(@square_left@@expression@@square_right@)*(@oper_suffix@@variable@)*

int<:["int""long""short""char"]

double<:"double"

float<:"float"

void<:"void"

sign<:["unsigned""signed"]

base_type<:[@int@@double@@float@@void@(@sign@(@segmentation@@int@)?)]

type<:[@base_type@@label@]

const<:"const"

const_type<:[(@const@@segmentation@@type@)(@type@@segmentation@@const@)]

extern_static<:["extern""static"]

extern_static_type<:[(@extern_static@@segmentation@@type@)|(@type@@segmentation@@extern_static@)]

register_volatile<:["register""volatile"]

register_volatile_type<:[(@register_volatile@@segmentation@@type@)(@type@@segmentation@@register_volatile@)]

extern_static_const<:[(@extern_static@@segmentation@@const@)(@const@@segmentation@@extern_static@)]

extern_static_const_type<:[(@extern_static_const@@segmentation@@type@)(@type@@segmentation@@extern_static_const@)]

extern_static_register_volatile<:[(@extern_static@@segmentation@@register_volatile@)(@register_volatile@@segmentation@@extern_static@)]

extern_static_register_volatile_type<:[(@extern_static_register_volatile@@segmentation@@type@)(@type@@segmentation@@extern_static_register_volatile@)]

const_register_volatile<:[(@const@@segmentation@@register_volatile@)(@register_volatile@@segmentation@@const@)]

const_register_volatile_type<:[(@const_register_volatile@@segmentation@@type@)(@type@@segmentation@@const_register_volatile@)]

arbitrarily_type<:[@const_register_volatile_type@@extern_static_register_volatile_type@
@extern_static_const_type@@register_volatile_type@@extern_static_type@@const_type@@type@]

pointer:"*"

address:"&"

address_s:@address@@variable@

block:@block_left@(@statement@@semicolon@)*@block_right@

scope:[@block@(@statement@)]

if:if@round@@scope@

else_if:elseif@round@@scope@

else:else@round@@scope@

if_else:@if@(@else_if@)*(@else@)?

break:"break"

break_process:[@break@@return_s@@goto@@proc_call@@expression@]

branch:@integer@@colon@[@block@(@break_process@+)]?

case:"case"

case_s:@case@@branch@

default:"default"

default_s:@default@@branch@

switch_case:@round@@block_left@@case_s@*@default_s@?@block_right@

continue:"continue"

break_continue_statement:[@break@@continue@@statement@]

break_continue_block:@block_left@@break_continue_statement@*@block_right@

once:[@break_continue_block@(@break_continue_statement@)]

while:"while"

while_s:@while@@round@@once@

do:"do"

do_while:@do@@once@@while@@round@

comma_expression:@expression@(@oper_comma@@expression@)*

for:"for"

for_s:@for@@round_left@(@statement@(@oper_comma@@statement@)*)|@semicolon@@comma_expression@|@semicolon@@comma_expression@|@round_right@@once@

arguments:@expression@(@oper_comma@@expression@)*

proc_call:@variable@@round_left@@arguments@?@round_right@

parameters:	@arbitrarily_type@@label@(@arbitrarily_type@@label@)*

proc_def:(@arbitrarily_type@@segmentation@@label@@round_left@@parameters@?@round_right@@block@)#ProcDef#

return<:"return"

return_s:@return@(@segmentation@@expression@)?

goto:goto@label@

assgin_label:@label@(@oper_as@@integer@)?

enum<:"enum"

enum_def:(@enum@@segmentation@@label@@block_left@(@assgin_label@@oper_comma@?)*@block_right@@semicolon@)#EnumDef#

body:@label@@block_left@([(@variable_def@@semicolon@)@enum_def@@struct_def@@union_def@])*@block_right@@semicolon@

struct<:"struct"

struct_def:(@struct@@segmentation@@body@)#StructDef#

union<:"union"

union_def:(@union@@segmentation@@body@)#UnionDef#

main:[@proc_def@@enum_def@@struct_def@@union_def@]