
annotation:"//".*$

string:\"[^\"]*\"

space:[ \t\r]

line:\n

ignore:(space|line)*

expression:@ignore@@oper_one@@expression@@ignore@
expression:@ignore@@expression@"++"@ignore@
expression:@ignore@@expression@"--"@ignore@
expression:@ignore@@expression@@oper_two@@expression@@ignore@
expression:@ignore@@expression@"?"@expression@":"@expression@@ignore@
expression:(@ignore@sizeof@ignore@@round@@ignore@)|(@ignore@sizeof(space|line)+@string@|@label@|@numeric@|@integer@@ignore@)
expression:@ignore@@variable@|@numeric@|@integer@@ignore@
expression:@ignore@"("@expression@")"@ignore@

oper_two:@oper_comma@|@oper_assgin@|@oper_logic_or@|@oper_logic_and@|@oper_bit_or@|@oper_bit_xor@|@oper_bit_and@|@oper_equal@|@oper_rela@|@oper_mov@|@oper_add_sub@|@oper_mul_div@

oper_comma:","	#printf(",\n")#
oper_assgin:"="|"+="|"-="|"*="|"/="|"%="|"&="|"^="|"|="|"<<="|">>="
oper_logic_or:"||"
oper_logic_and:"&&"
oper_bit_or:"|"
oper_bit_xor:"^"
oper_bit_and:"&"
oper_equal:"=="|"!="
oper_rela:"<"|"<="|">"|">="
oper_mov:"<<"|">>"
oper_add_sub:"+"|"-"
oper_mul_div:"*"|"/"|"%"

oper_one:"-"|"++"|"--"|"!"|"~"|"+"|"-"|"*"|"&"
type_cast:"("@label@")"

oper_suffix:"."|"->"
round:"("@expression@")"

label:[_a-zA-Z][a-zA-Z0-9]*

keywords:struct|break|else|switch|case|enum|register|typedef|extern|return|union|const|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|if|while|static

numeric:@integer@\.@integer@

integer:[0-9]+

variable:@pointer@*@label@("["@expression@"]")*

base_type:auto|double|int|long|char|float

type:@base_type@|@label@

const_type:(const@ignore@@type@)|(@type@@ignore@const)

static_type:(static@ignore@@type@)|(@type@@ignore@static)

static_const:(static@ignore@const)|(const@ignore@static)

static_const_type:(@static_const@@ignore@@type@)|(@type@@ignore@@static_const@)

arbitrarily_type:@static_const_type@|@static_type@|@const_type@

pointer:"*"@ignore@

address:"&"@ignore@@label@|"&"@ignore@@label@"["@expression@"]"

scope:("{"@ignore@@statements@@ignore@"}")|(@ignore@@statement@@ignore@)

condition:"("@ignore@@expression@@ignore@")"

if:if@ignore@@condition@@ignore@@scope@

else_if:else@ignore@if@ignore@@condition@@ignore@@scope@

else:else@ignore@@condition@@ignore@@scope@

if_else:@if@(@ignore@@else_if@@ignore@)*(@ignore@@else@)?

case:case@ignore@@variable@|@integer@@ignore@("{"@ignore@@statements@@ignore@"}")|(@ignore@@processes@@ignore@)

default:default@ignore@@variable@|@integer@@ignore@("{"@ignore@@statements@@ignore@"}")|(@ignore@@processes@@ignore@)

switch_case:@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@case@*@default@?@ignore@"}"

while:while@ignore@@condition@@ignore@@scope@

do_while:do@ignore@@scope@@ignore@while@ignore@@condition@

for:for@ignore@"("@ignore@@expression@@ignore@";"@ignore@@expression@@ignore@";"@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"

arguments:@expression@(@ignore@@oper_comma@@ignore@@expression@)*

proc_call:@variable@"("arguments?")"

parameters:	@arbitrarily_type@@label@(@ignore@@arbitrarily_type@@ignore@@label@)*

proc_def:void|@arbitrarily_type@@ignore@"("@ignore@@parameters@?@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"