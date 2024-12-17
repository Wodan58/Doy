/*
 * generated Fri Oct 11 15:34:20 2024
 */
#include "globals.h"
#define PARM(n, m)
#include "builtin.h"

void joy(pEnv env)
{
NULLARY(INTEGER_NEWNODE, 35);
static Node L1[] = {
{ .u.proc=small_, .op=ANON_FUNCT_ },
{ .u.proc=dup_, .op=ANON_FUNCT_ },
};
NULLARY(LIST_NEWNODE, L1);

LIST_NULLNODE;

static Node L2[] = {
{ .u.proc=pred_, .op=ANON_FUNCT_ },
{ .u.proc=dup_, .op=ANON_FUNCT_ },
{ .u.proc=pred_, .op=ANON_FUNCT_ },
};
NULLARY(LIST_NEWNODE, L2);

static Node L3[] = {
{ .u.proc=plus_, .op=ANON_FUNCT_ },
};
NULLARY(LIST_NEWNODE, L3);

binrec_(env);
/* JOY */
}

#include "defines.h"

#undef DUP_C
#undef PLUS_C
#undef PRED_C
#undef SMALL_C
#undef BINREC_C

table_t yytable[] = {
{ dup_, "dup" },
{ plus_, "+" },
{ pred_, "pred" },
{ small_, "small" },
{ binrec_, "binrec" },
{ 0 }
};

#include "depends.h"
#include "builtin.c"
