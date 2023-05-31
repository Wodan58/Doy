#
#   module  : makefile
#   version : 1.3
#   date    : 11/23/20
#
#	Makefile voor various versions of Joy.
#
#	Joy is a translation of the Pascal sources, with a number of
#	corrections, extended with getch and putch and hyphen not as a
#	separate symbol.
#
#	Recipe for adding a new builtin:
#
#	1. Create a .c file with the code of the new builtin
#	2. Add the .c file to the makefile
#	3. Add the new builtin to standardindent in ident.h
#	4. Add the new builtin to initialise in initsym.c
#	5. Add the name of the builtin to standardident_NAMES in dump.c
#	6. Add a description of the builtin to prims.c
#
ASM = nasm
AFLAGS = -o$@ -felf64 -l$*.lst

CC = gcc -o$@
CFLAGS = -DNDEBUG -I.. -Os -Wall -Wextra

ARFLAGS = rvU

DO = libdo.a

DOLIB :	$(DO)(aux_eql.o) $(DO)(do_add.o) $(DO)(do_and.o) $(DO)(do_body.o) \
	$(DO)(do_cons.o) $(DO)(do_dip.o) $(DO)(do_dup.o) $(DO)(do_eql.o) \
	$(DO)(do_false.o) $(DO)(do_get.o) $(DO)(do_index.o) $(DO)(do_i.o) \
	$(DO)(do_lss.o) $(DO)(do_mul.o) $(DO)(do_nothing.o) $(DO)(do_not.o) \
	$(DO)(do_or.o) $(DO)(do_pop.o) $(DO)(do_putch.o) $(DO)(do_put.o) \
	$(DO)(do_sametype.o) $(DO)(do_stack.o) $(DO)(do_step.o) \
	$(DO)(do_stop.o) $(DO)(do_sub.o) $(DO)(do_swap.o) $(DO)(do_true.o) \
	$(DO)(do_uncons.o) $(DO)(do_unstack.o) $(DO)(is_char.o) \
	$(DO)(is_file.o) $(DO)(is_float.o) $(DO)(is_integer.o) \
	$(DO)(is_list.o) $(DO)(is_logical.o) $(DO)(is_set.o) \
	$(DO)(is_string.o) $(DO)(is_user.o) $(DO)(aux_decode.o) \
	$(DO)(aux_time.o) $(DO)(do_abort.o) $(DO)(do_abs.o) $(DO)(do_all.o) \
	$(DO)(do_app11.o) $(DO)(do_app12.o) $(DO)(do_app1.o) $(DO)(do_app2.o) \
	$(DO)(do_app3.o) $(DO)(do_app4.o) $(DO)(do_argc.o) $(DO)(do_argv.o) \
	$(DO)(do_at.o) $(DO)(do_autoput.o) $(DO)(do_binary.o) \
	$(DO)(do_binrec.o) $(DO)(do_branch.o) $(DO)(do_builtin.o) \
	$(DO)(do_case.o) $(DO)(do_choice.o) $(DO)(do_chr.o) $(DO)(do_cleave.o) \
	$(DO)(do_clock.o) $(DO)(do_compare.o) $(DO)(do_concat.o) \
	$(DO)(do_condlinrec.o) $(DO)(do_condnestrec.o) $(DO)(do_cond.o) \
	$(DO)(do_construct.o) $(DO)(do_conts.o) $(DO)(do_divide.o) \
	$(DO)(do_div.o) $(DO)(do_drop.o) $(DO)(do_dump.o) $(DO)(do_dupd.o) \
	$(DO)(do_echo.o) $(DO)(do_enconcat.o) $(DO)(do_equal.o) \
	$(DO)(do_fclose.o) $(DO)(do_feof.o) $(DO)(do_ferror.o) \
	$(DO)(do_fflush.o) $(DO)(do_fgetch.o) $(DO)(do_fget.o) \
	$(DO)(do_fgets.o) $(DO)(do_filter.o) $(DO)(do_first.o) \
	$(DO)(do_fold.o) $(DO)(do_fopen.o) $(DO)(do_formatf.o) \
	$(DO)(do_format.o) $(DO)(do_fputchars.o) $(DO)(do_fputch.o) \
	$(DO)(do_fput.o) $(DO)(do_fputstring.o) $(DO)(do_fread.o) \
	$(DO)(do_fremove.o) $(DO)(do_frename.o) $(DO)(do_fseek.o) \
	$(DO)(do_ftell.o) $(DO)(do_fwrite.o) $(DO)(do_gc.o) $(DO)(do_genrec.o) \
	$(DO)(do_geq.o) $(DO)(do_getch.o) $(DO)(do_getenv.o) \
	$(DO)(do_gmtime.o) $(DO)(do_gtr.o) $(DO)(do_has.o) $(DO)(do_help1.o) \
	$(DO)(do_helpdetail.o) $(DO)(do_help.o) $(DO)(do_html_manual.o) \
	$(DO)(do_id.o) $(DO)(do_ifchar.o) $(DO)(do_iffile.o) \
	$(DO)(do_iffloat.o) $(DO)(do_ifinteger.o) $(DO)(do_iflist.o) \
	$(DO)(do_iflogical.o) $(DO)(do_ifset.o) $(DO)(do_ifstring.o) \
	$(DO)(do_ifte.o) $(DO)(do_include.o) $(DO)(do_infra.o) $(DO)(do_in.o) \
	$(DO)(do_intern.o) $(DO)(do_char.o) $(DO)(do_file.o) $(DO)(do_float.o) \
	$(DO)(do_integer.o) $(DO)(do_list.o) $(DO)(do_logical.o) \
	$(DO)(do_set.o) $(DO)(do_string.o) $(DO)(do_user.o) \
	$(DO)(do_latex_manual.o) $(DO)(do_leaf.o) $(DO)(do_leq.o) \
	$(DO)(do_linrec.o) $(DO)(do_localtime.o) $(DO)(do_manual_list.o) \
	$(DO)(do_manual.o) $(DO)(do_map.o) $(DO)(do_maxint.o) $(DO)(do_max.o) \
	$(DO)(do_memoryindex.o) $(DO)(do_memorymax.o) $(DO)(do_min.o) \
	$(DO)(do_mktime.o) $(DO)(do_name.o) $(DO)(do_neg.o) $(DO)(do_neq.o) \
	$(DO)(do_nullary.o) $(DO)(do_null.o) $(DO)(do_of.o) $(DO)(do_opcase.o) \
	$(DO)(do_ord.o) $(DO)(do_popd.o) $(DO)(do_pred.o) $(DO)(do_primrec.o) \
	$(DO)(do_putchars.o) $(DO)(do_quit.o) $(DO)(do_rand.o) $(DO)(do_rem.o) \
	$(DO)(do_rest.o) $(DO)(do_rolldownd.o) $(DO)(do_rolldown.o) \
	$(DO)(do_rollupd.o) $(DO)(do_rollup.o) $(DO)(do_rotated.o) \
	$(DO)(do_rotate.o) $(DO)(do_select.o) $(DO)(do_setautoput.o) \
	$(DO)(do_setecho.o) $(DO)(do_setlisting.o) $(DO)(do_setsize.o) \
	$(DO)(do_setstats.o) $(DO)(do_settracegc.o) $(DO)(do_settrace.o) \
	$(DO)(do_setundeferror.o) $(DO)(do_sign.o) $(DO)(do_size.o) \
	$(DO)(do_small.o) $(DO)(do_some.o) $(DO)(do_split.o) $(DO)(do_srand.o) \
	$(DO)(do_stderr.o) $(DO)(do_stdin.o) $(DO)(do_stdout.o) \
	$(DO)(do_strftime.o) $(DO)(do_strtol.o) $(DO)(do_succ.o) \
	$(DO)(do_swapd.o) $(DO)(do_swons.o) $(DO)(do_symtabindex.o) \
	$(DO)(do_symtabmax.o) $(DO)(do_system.o) $(DO)(do_tailrec.o) \
	$(DO)(do_take.o) $(DO)(do_ternary.o) $(DO)(do_time.o) \
	$(DO)(do_times.o) $(DO)(do_treegenrec.o) $(DO)(do_treerec.o) \
	$(DO)(do_treestep.o) $(DO)(do_unary2.o) $(DO)(do_unary3.o) \
	$(DO)(do_unary4.o) $(DO)(do_unary.o) $(DO)(do_undeferror.o) \
	$(DO)(do_undefs.o) $(DO)(do_unswons.o) $(DO)(do_while.o) $(DO)(do_x.o) \
	$(DO)(do_xor.o) $(DO)(prims.o) $(DO)(setebp.o) $(DO)(do_acos.o) \
	$(DO)(do_asin.o) $(DO)(do_atan2.o) $(DO)(do_atan.o) $(DO)(do_ceil.o) \
	$(DO)(do_cosh.o) $(DO)(do_cos.o) $(DO)(do_exp.o) $(DO)(do_floor.o) \
	$(DO)(do_frexp.o) $(DO)(do_ldexp.o) $(DO)(do_log10.o) $(DO)(do_log.o) \
	$(DO)(do_modf.o) $(DO)(do_mod.o) $(DO)(do_pow.o) $(DO)(do_sinh.o) \
	$(DO)(do_sin.o) $(DO)(do_sqrt.o) $(DO)(do_strtod.o) $(DO)(do_tanh.o) \
	$(DO)(do_tan.o) $(DO)(do_trunc.o)

.s.o:
	$(ASM) $(AFLAGS) $<

clean:
	rm -f *.a
