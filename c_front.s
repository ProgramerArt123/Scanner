
annotation:"//".*$

string:\"[("\".)^\"]*\"

?:[@annotation@\s*]

?segmentation<:\s+

variable_def:(@arbitrarily_type@@segmentation@@variable@("="@expression@)?)#VariableDef#

statement:[@return@@goto@@proc_call@@variable_def@@expression@]

expression:[(@oper_one@@variable@)(@variable@["++""--"])(@element@(@oper_two@@element@)*)]

element:[("("@expression@")")@proc_call@@string@@variable@@numeric@@integer@@address@@sizeof@]

sizeof:[(sizeof"("@expression@")")(sizeof@element@)]

oper_two:[","@oper_assgin@@oper_logic_or@@oper_logic_and@@oper_bit_or@@oper_bit_xor@@oper_bit_and@@oper_equal@@oper_rela@@oper_mov@@oper_add_sub@@oper_mul_div@]

oper_comma:","
oper_assgin:["=""+=""-=""*=""/=""%=""&=""^=""|=""<<="">>="]
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

oper_one:["-""++""--""!""~""+""-""*""&"]
type_cast:"("@label@")"

oper_suffix:[".""->"]
round:"("@expression@")"

label:[_a-zA-Z][_a-zA-Z0-9]*

numeric:@integer@("."@integer@)?

integer:[0-9]+

variable:@pointer@*@label@("["@expression@"]")*(@oper_suffix@@variable@)*

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

arbitrarily_type<:[@const_register_volatile_type@@extern_static_register_volatile_type@@extern_static_const_type@@register_volatile_type@@extern_static_type@@const_type@@type@]

pointer:"*"

address:"&"@variable@

block:"{"(@statement@";")*"}"

scope:[@block@(@statement@)]

if:if@round@@scope@

else_if:elseif@round@@scope@

else:else@round@@scope@

if_else:@if@(@else_if@)*(@else@)?

break_process:["break"@return@@goto@@proc_call@@expression@]

branch:@integer@":"[@block@(@break_process@+)]?

case:"case"@branch@

default:"default"@branch@

switch_case:@round@"{"@case@*@default@?"}"

break_continue_statement:["break""continue"@statement@]

break_continue_block:"{"@break_continue_statement@*"}"

once:[@break_continue_block@(@break_continue_statement@)]

while:"while"@round@@once@

do_while:do@once@"while"@round@

comma_expression:@expression@(@oper_comma@@expression@)*

for:"for""("(@statement@(@oper_comma@@statement@)*)|";"@comma_expression@|";"@comma_expression@|")"@once@

arguments:@expression@(","@expression@)*

proc_call:@variable@"("@arguments@?")"

parameters:	@arbitrarily_type@@label@(@arbitrarily_type@@label@)*

proc_def:(@arbitrarily_type@@segmentation@@label@"("@parameters@?")"@block@)#ProcDef#

ret<:"return"

return:@ret@(@segmentation@@expression@)?

goto:goto@label@

labels:@label@(@oper_comma@@label@)+)|@label@

assgin_label:@label@("="@integer@)?

enum_def:("enum"@label@"{"(@assgin_label@","?)*"}"";")#EnumDef#

body:@label@"{"([(@variable_def@";")@enum_def@@struct_def@@union_def@])*"}"";"

struct<:"struct"

struct_def:(@struct@@segmentation@@body@)#StructDef#

union_def:("union"@body@)#UnionDef#

main:[@proc_def@@enum_def@@struct_def@@union_def@]