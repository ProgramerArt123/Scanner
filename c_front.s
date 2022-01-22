
annotation:"//".*$

string:\"^\"*\"

ignore:[@annotation@\s*]

segmentation:\s+

variable_def:@arbitrarily_type@@ignore@@variable@(@ignore@"="@ignore@@expression@)?

statement:[@return@@goto@@proc_call@@variable_def@@expression@]

expression:[(@oper_one@@ignore@@variable@)(@variable@@ignore@["++""--"])(@element@(@ignore@@oper_two@@ignore@@element@)*)]

element:[("("@ignore@@expression@@ignore@")")@proc_call@@string@@variable@@numeric@@integer@@address@@sizeof@]

sizeof:[(sizeof@ignore@"("@ignore@@expression@@ignore@")")(sizeof@ignore@@element@)]

oper_two:[","@oper_assgin@@oper_logic_or@@oper_logic_and@@oper_bit_or@@oper_bit_xor@@oper_bit_and@@oper_equal@@oper_rela@@oper_mov@@oper_add_sub@@oper_mul_div@]

oper_comma:(",")#SetComma#
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

int:["int""long""short""char"]

base_type:[@int@"double""float""void"(["unsigned""signed"](@segmentation@@int@)?)]

type:[@base_type@@label@]

const:"const"

const_type:[(@const@@segmentation@@type@)(@type@@segmentation@@const@)]

extern_static:["extern""static"]

extern_static_type:[(@extern_static@@segmentation@@type@)|(@type@@segmentation@@extern_static@)]

register_volatile:["register""volatile"]

register_volatile_type:[(@register_volatile@@segmentation@@type@)(@type@@segmentation@@register_volatile@)]

extern_static_const:[(@extern_static@@segmentation@@const@)(@const@@segmentation@@extern_static@)]

extern_static_const_type:[(@extern_static_const@@segmentation@@type@)(@type@@segmentation@@extern_static_const@)]

extern_static_register_volatile:[(@extern_static@@segmentation@@register_volatile@)(@register_volatile@@segmentation@@extern_static@)]

extern_static_register_volatile_type:[(@extern_static_register_volatile@@segmentation@@type@)(@type@@segmentation@@extern_static_register_volatile@)]

const_register_volatile:[(@const@@segmentation@@register_volatile@)(@register_volatile@@segmentation@@const@)]

const_register_volatile_type:[(@const_register_volatile@@segmentation@@type@)(@type@@segmentation@@const_register_volatile@)]

arbitrarily_type:[@const_register_volatile_type@@extern_static_register_volatile_type@@extern_static_const_type@@register_volatile_type@@extern_static_type@@const_type@@type@]

pointer:"*"@ignore@

address:"&"@ignore@@variable@

block:"{"(@ignore@@statement@@ignore@";")*@ignore@"}"

scope:[@block@(@ignore@@statement@@ignore@)]

if:if@ignore@@round@@ignore@@scope@

else_if:else@ignore@if@ignore@@round@@ignore@@scope@

else:else@ignore@@round@@ignore@@scope@

if_else:@if@(@ignore@@else_if@@ignore@)*(@ignore@@else@)?

break_process:["break"@return@@goto@@proc_call@@expression@]

branch:@integer@@ignore@":"@ignore@[@block@(@ignore@@break_process@+@ignore@)]?

case:"case"@ignore@@branch@

default:"default"@ignore@@branch@

switch_case:@ignore@@round@@ignore@"{"@ignore@@case@*@default@?@ignore@"}"

break_continue_statement:["break""continue"@statement@]

break_continue_block:"{"@ignore@@break_continue_statement@*@ignore@"}"

once:[@break_continue_block@(@ignore@@break_continue_statement@@ignore@)]

while:"while"@ignore@@round@@ignore@@once@

do_while:do@ignore@@once@@ignore@"while"@ignore@@round@

comma_expression:@expression@(@oper_comma@@expression@)*

for:"for"@ignore@"("@ignore@(@statement@@ignore@(@ignore@@oper_comma@@ignore@@statement@)*)|";"@ignore@@comma_expression@@ignore@|";"@ignore@@comma_expression@@ignore@|")"@ignore@@once@

arguments:@expression@(@ignore@","@ignore@@expression@)*

proc_call:@variable@@ignore@"("@ignore@@arguments@?@ignore@")"

parameters:	@arbitrarily_type@@label@(@ignore@@arbitrarily_type@@ignore@@label@)*

proc_def:@arbitrarily_type@@segmentation@@label@@ignore@"("@ignore@@parameters@?@ignore@")"@ignore@@block@

return:"return"(@segmentation@@expression@)?

goto:goto@ignore@@label@

labels:@label@(@ignore@@oper_comma@@ignore@@label@)+)|@label@

assgin_label:@label@@ignore@(@ignore@"="@ignore@@integer@)?

enum_def:"enum"@ignore@@label@@ignore@"{"(@ignore@@assgin_label@@ignore@","?)*@ignore@"}"@ignore@";"

body:@label@@ignore@"{"@ignore@([(@variable_def@@ignore@";")@struct_def@@union_def@]@ignore@)*"}"@ignore@";"

struct_def:"struct"@ignore@@body@

union_def:"union"@ignore@@body@

main:@ignore@[@proc_def@@enum_def@@struct_def@@union_def@]@ignore@