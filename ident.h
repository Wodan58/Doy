/*
    module  : ident.h
    version : 1.2
    date    : 10/26/20
*/
typedef enum {
    lib_,
    typ_symbol, typ_logical, typ_char, typ_integer, typ_set, typ_string,
    typ_list, typ_float, typ_file, typ_function,
    def_module, def_private, def_public, def_equal, def_end, dir_if,
    dir_include, dir_listing, dir_put, dir_radix, dir_set, dir_statistics,
    dir_trace,
    mul_, add_, sub_, divide_, lss_, eql_, and_, body_, cons_, dip_, dup_,
    false_, get_, getch_, i_, index_, not_, nothing_, or_, pop_, put_, putch_,
    sametype_, select_, stack_, step_, swap_, true_, uncons_, unstack_,
    maxint_,
    aux_genrec_, aux_treerec_, aux_treegenrec_, setsize_, __symtabmax_,
    __symtabindex_, __dump_, conts_, autoput_, undeferror_, undefs_, echo_,
    clock_, time_, rand_, __memorymax_, stdin_, stdout_, stderr_, id_, rollup_,
    rolldown_, rotate_, popd_, dupd_, swapd_, rollupd_, rolldownd_, rotated_,
    choice_, xor_, rem_, div_, sign_, neg_, ord_, chr_, abs_, acos_, asin_,
    atan_, atan2_, ceil_, cos_, cosh_, exp_, floor_, frexp_, ldexp_, log_,
    log10_, modf_, pow_, sin_, sinh_, sqrt_, tan_, tanh_, trunc_, localtime_,
    gmtime_, mktime_, strftime_, strtol_, strtod_, format_, formatf_, srand_,
    pred_, succ_, max_, min_, fclose_, feof_, ferror_, fflush_, fgetch_,
    fgets_, fopen_, fread_, fwrite_, fremove_, frename_, fput_, fputch_,
    fputchars_, fputstring_, fseek_, ftell_, swons_, first_, rest_, compare_,
    at_, of_, size_, opcase_, case_, unswons_, drop_, take_, concat_,
    enconcat_, name_, intern_, null_, small_, geq_, gtr_, leq_, neq_, equal_,
    has_, in_, integer_, char_, logical_, set_, string_, list_, leaf_, user_,
    float_, file_, x_, app1_, app11_, app12_, construct_, nullary_, unary_,
    unary2_, unary3_, unary4_, app2_, app3_, app4_, binary_, ternary_, cleave_,
    branch_, ifte_, ifinteger_, ifchar_, iflogical_, ifset_, ifstring_,
    iflist_, iffloat_, iffile_, cond_, while_, linrec_, tailrec_, binrec_,
    genrec_, condnestrec_, condlinrec_, fold_, map_, times_, infra_, primrec_,
    filter_, split_, some_, all_, treestep_, treerec_, treegenrec_, help_,
    _help_, helpdetail_, manual_, __html_manual_, __latex_manual_,
    __manual_list_, __settracegc_, setautoput_, setundeferror_, setecho_, gc_,
    system_, getenv_, argv_, argc_, __memoryindex_, putchars_, include_,
    abort_, quit_, __setlisting_, __setstats_, __settrace_, builtin_, fget_,
    mod_, stop_, unknownident
} standardident;
