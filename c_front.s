
annotation:"//".*$

string:\"[("\".)^\"]*\"

?:[@annotation@\s+]

?segmentation<:\s+

integer:[0-9]+

label_head<:[_a-zA-Z]

label:@label_head@[_a-zA-Z0-9]*



semicolon:";"

comma:","

colon:":"

oper_eq:"="

oper_add:"+"

oper_sub:"-"

oper_inc:"++"

oper_dec:"--"

oper_dot:"."

round_left:"("

round_right:")"

square_left:"["

square_right:"]"

block_left:"{"

block_right:"}"

oper_assgin:[@oper_eq@"+=""-=""*=""/=""%=""&=""^=""|=""<<="">>="]

oper_logic_or:"||"

oper_logic_and:"&&"

oper_bit_or:"|"

oper_bit_xor:"^"

oper_bit_and:"&"

oper_equal:["==""!="]

oper_rela:["<="">=""<"">"]

oper_mov:["<<"">>"]

oper_add_sub:[@oper_add@@oper_sub@]

oper_mul_div:["*""/""%"]

oper_one:[@oper_inc@@oper_dec@"!""~"@oper_add@@oper_sub@"*""&"]

oper_suffix:[@oper_dot@"->"]

oper_two:[@comma@@oper_equal@@oper_assgin@@oper_logic_or@
@oper_logic_and@@oper_bit_or@@oper_bit_xor@@oper_bit_and@
@oper_rela@@oper_mov@@oper_add_sub@@oper_mul_div@]







int<:["int""long""short""char"]

double<:"double"

float<:"float"

void<:"void"

sign<:["unsigned""signed"]

const<:"const"

extern_static<:["extern""static"]

register_volatile<:["register""volatile"]

return<:"return"

enum<:"enum"

struct<:"struct"

union<:"union"

sizeof<:"sizeof"

base_type<:[@int@@double@@float@@void@(@sign@(@segmentation@@int@)?)]

type<:[@base_type@@label@]

const_type<:[(@const@@segmentation@@type@)(@type@@segmentation@@const@)]

extern_static_type<:[(@extern_static@@segmentation@@type@)
	(@type@@segmentation@@extern_static@)]

register_volatile_type<:[(@register_volatile@@segmentation@@type@)
	(@type@@segmentation@@register_volatile@)]

extern_static_const<:[(@extern_static@@segmentation@@const@)
	(@const@@segmentation@@extern_static@)]

extern_static_const_type<:[(@extern_static_const@@segmentation@@type@)
	(@type@@segmentation@@extern_static_const@)]

extern_static_register_volatile<:[(@extern_static@@segmentation@@register_volatile@)
	(@register_volatile@@segmentation@@extern_static@)]

extern_static_register_volatile_type<:[(@extern_static_register_volatile@@segmentation@@type@)
	(@type@@segmentation@@extern_static_register_volatile@)]

const_register_volatile<:[(@const@@segmentation@@register_volatile@)
	(@register_volatile@@segmentation@@const@)]

const_register_volatile_type<:[(@const_register_volatile@@segmentation@@type@)
	(@type@@segmentation@@const_register_volatile@)]

arbitrarily_type<:[@const_register_volatile_type@@extern_static_register_volatile_type@
	@extern_static_const_type@@register_volatile_type@@extern_static_type@@const_type@@type@]



pointer:"*"

if:"if"

else:"else"

break:"break"

case:"case"

default:"default"

continue:"continue"

while:"while"

do:"do"

for:"for"





numeric:@integer@(@oper_dot@@integer@)?

variable:@pointer@*@label@(@square_left@@expression@@square_right@)*(@oper_suffix@@variable@)*

sizeof_s:@sizeof@[(@segmentation@?@round@)(@segmentation@@element@)]

element:[@round@@proc_call@@string@@variable@@numeric@@integer@@address@@sizeof_s@]

address:@oper_bit_and@@variable@

type_cast:@round_left@@label@@round_right@

expression:[(@oper_one@@variable@)
			(@variable@[@oper_inc@@oper_dec@])
			(@element@(@oper_two@@element@)*)]

return_s:@return@(@segmentation@@expression@)?

goto:goto@label@

proc_call:@variable@@round_left@@arguments@?@round_right@




round:@round_left@@expression@@round_right@

statement:[@if_else_s@
	([@do_while_s@@return_s@@goto@@proc_call@@variable_def@@expression@]@semicolon@)]

block:@block_left@@statement@*@block_right@

scope:[@block@@statement@]

comma_expression:@expression@(@comma@@expression@)*

arguments:@expression@(@comma@@expression@)*

parameters:	@arbitrarily_type@@label@(@arbitrarily_type@@label@)*

assgin_label:@label@(@oper_eq@@integer@)?

body:@label@@block_left@([(@variable_def@@semicolon@)
	@enum_def@@struct_def@@union_def@])*@block_right@@semicolon@






break_process:[@break@@return_s@@goto@@proc_call@@expression@]

branch:@integer@@colon@[@block@(@break_process@+)]?

case_s:@case@@branch@

default_s:@default@@branch@

switch_case:@round@@block_left@@case_s@*@default_s@?@block_right@

break_continue_statement:[((@break@@continue@)@semicolon@)@statement@]

break_continue_block:@block_left@@break_continue_statement@*@block_right@

once:[@break_continue_block@@break_continue_statement@]





if_s:@if@@round@@scope@

else_if_s:@else@@if@@round@@scope@

else_s:@else@@scope@

if_else_s:@if_s@@else_if_s@*@else_s@?

do_while_s:@do@@once@@while@@round@

while_s:@while@@round@@once@

for_s:@for@@round_left@(@statement@(@comma@@statement@)*)|
	@semicolon@@comma_expression@|@semicolon@@comma_expression@|@round_right@@once@









variable_def:(@arbitrarily_type@@segmentation@@variable@
	(@oper_eq@@expression@)?)#VariableDef#

proc_def:(@arbitrarily_type@@segmentation@@label@
	@round_left@@parameters@?@round_right@@block@)#ProcDef#

enum_def:(@enum@@segmentation@@label@@block_left@
	(@assgin_label@@comma@?)*@block_right@@semicolon@)#EnumDef#

struct_def:(@struct@@segmentation@@body@)#StructDef#

union_def:(@union@@segmentation@@body@)#UnionDef#

main:[@proc_def@@enum_def@@struct_def@@union_def@]