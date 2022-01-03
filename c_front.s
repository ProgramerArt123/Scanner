
annotation:"//".*$

string:\"[^\"]*\"

space:[ \t\r]

line:\n

ignore:(space|line)+

expression:@ignore@@oper_one@@ignore@@expression@@ignore@
expression:@ignore@@expression@@ignore@"++"
expression:@ignore@@expression@@ignore@"--"
expression:@ignore@@expression@@ignore@@oper_two@@ignore@@expression@@ignore@
expression:@ignore@@expression@@ignore@"?"@ignore@@expression@@ignore@":"@ignore@@expression@@ignore@
expression:(sizeof@round@)|(sizeof +@string@|@label@|@numeric@|@integer@)
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

keywords:auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|const|float|short|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|if|while|static

label:[_a-zA-Z][a-zA-Z0-9]*

numeric:@integer@\.@integer@

integer:[0-9]+

