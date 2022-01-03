
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
expression:@ignore@@round@@ignore@

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

keywords:struct|break|enum|register|typedef|extern|return|union|unsigned|continue|signed|void|goto|volatile

numeric:@integer@\.@integer@

integer:[0-9]+

variable:@pointer@*@label@("["@expression@"]")*

base_type:auto|double|int|long|char|float|void

type:@base_type@|@label@

const_type:(const@ignore@@type@)|(@type@@ignore@const)

static_type:(static@ignore@@type@)|(@type@@ignore@static)

static_const:(static@ignore@const)|(const@ignore@static)

static_const_type:(@static_const@@ignore@@type@)|(@type@@ignore@@static_const@)

arbitrarily_type:@static_const_type@|@static_type@|@const_type@

pointer:"*"@ignore@

address:"&"@ignore@@label@|"&"@ignore@@label@"["@expression@"]"

block:"{"@ignore@@statements@@ignore@"}"

scope:@block@|(@ignore@@statement@@ignore@)

if:if@ignore@@round@@ignore@@scope@

else_if:else@ignore@if@ignore@@round@@ignore@@scope@

else:else@ignore@@round@@ignore@@scope@

if_else:@if@(@ignore@@else_if@@ignore@)*(@ignore@@else@)?

branch:@variable@|@integer@@ignore@@block@|(@ignore@@processes@@ignore@)

case:case@ignore@@branch@

default:default@ignore@@branch@

switch_case:@ignore@@round@@ignore@"{"@ignore@@case@*@default@?@ignore@"}"

while:while@ignore@@round@@ignore@@scope@

do_while:do@ignore@@scope@@ignore@while@ignore@@round@

comma_process:@processes@(@oper_comma@@processes@)*"

for:for@ignore@"("@ignore@(@statement@@ignore@(@ignore@@oper_comma@@ignore@@statement@)*)|";"@ignore@@comma_process@@ignore@|";"@ignore@@comma_process@@ignore@|")"@ignore@@scope@

arguments:@expression@(@ignore@@oper_comma@@expression@)*

proc_call:@variable@"("arguments?")"

parameters:	@arbitrarily_type@@label@(@ignore@@arbitrarily_type@@ignore@@label@)*

proc_def:@arbitrarily_type@@ignore@"("@ignore@@parameters@?@ignore@")"@ignore@@block@