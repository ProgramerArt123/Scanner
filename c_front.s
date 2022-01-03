
annotation:"//".*$

string:\"[^\"]*\"

space:[ \t\r]

line:\n

ignore:(space|line)*



expression:@ignore@@oper_one@@ignore@@expression@@ignore@
expression:@ignore@@expression@@ignore@"++"
expression:@ignore@@expression@@ignore@"--"
expression:@ignore@@expression@@ignore@@oper_two@@ignore@@expression@@ignore@
expression:@ignore@@expression@@ignore@"?"@ignore@@expression@@ignore@":"@ignore@@expression@@ignore@
expression:(sizeof@round@)|(sizeof +@string@|@label@|@numeric@|@integer@)
expression:@variable@|@numeric@|@integer@
expression:"("@expression@")"

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

variable:@pointer@*@label@|@pointer@*@label@"["@expression@"]"


base_type:auto|double|int|long|char|float

pointer:"*"@ignore@

address:"&"@ignore@@label@|"&"@ignore@@label@"["@expression@"]"

if:if@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"@ignore@

else_if:else@ignore@if@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"@ignore@

else:else@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"@ignore@

while:while@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"

do_while:do@ignore@"("@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"@ignore@while

for:for@ignore@"("@ignore@@expression@@ignore@";"@ignore@@expression@@ignore@";"@ignore@@expression@@ignore@")"@ignore@"{"@ignore@@statements@@ignore@"}"@ignore@

arguments:@expression@(@oper_comma@@expression@)*

proc_call:@variable@"("arguments?")"