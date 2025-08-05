#ifndef LLM_REFLECTION_HPP
#define LLM_REFLECTION_HPP

#include <string_view>
#include <tuple>

#define MAKE_ARG_LIST_1(op, arg, ...) op(arg)
#define MAKE_ARG_LIST_2(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_1(op, __VA_ARGS__))
#define MAKE_ARG_LIST_3(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_2(op, __VA_ARGS__))
#define MAKE_ARG_LIST_4(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_3(op, __VA_ARGS__))
#define MAKE_ARG_LIST_5(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_4(op, __VA_ARGS__))
#define MAKE_ARG_LIST_6(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_5(op, __VA_ARGS__))
#define MAKE_ARG_LIST_7(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_6(op, __VA_ARGS__))
#define MAKE_ARG_LIST_8(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_7(op, __VA_ARGS__))
#define MAKE_ARG_LIST_9(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_8(op, __VA_ARGS__))
#define MAKE_ARG_LIST_10(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_9(op, __VA_ARGS__))
#define MAKE_ARG_LIST_11(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_10(op, __VA_ARGS__))
#define MAKE_ARG_LIST_12(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_11(op, __VA_ARGS__))
#define MAKE_ARG_LIST_13(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_12(op, __VA_ARGS__))
#define MAKE_ARG_LIST_14(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_13(op, __VA_ARGS__))
#define MAKE_ARG_LIST_15(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_14(op, __VA_ARGS__))
#define MAKE_ARG_LIST_16(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_15(op, __VA_ARGS__))
#define MAKE_ARG_LIST_17(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_16(op, __VA_ARGS__))
#define MAKE_ARG_LIST_18(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_17(op, __VA_ARGS__))
#define MAKE_ARG_LIST_19(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_18(op, __VA_ARGS__))
#define MAKE_ARG_LIST_20(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_19(op, __VA_ARGS__))
#define MAKE_ARG_LIST_21(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_20(op, __VA_ARGS__))
#define MAKE_ARG_LIST_22(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_21(op, __VA_ARGS__))
#define MAKE_ARG_LIST_23(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_22(op, __VA_ARGS__))
#define MAKE_ARG_LIST_24(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_23(op, __VA_ARGS__))
#define MAKE_ARG_LIST_25(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_24(op, __VA_ARGS__))
#define MAKE_ARG_LIST_26(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_25(op, __VA_ARGS__))
#define MAKE_ARG_LIST_27(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_26(op, __VA_ARGS__))
#define MAKE_ARG_LIST_28(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_27(op, __VA_ARGS__))
#define MAKE_ARG_LIST_29(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_28(op, __VA_ARGS__))
#define MAKE_ARG_LIST_30(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_29(op, __VA_ARGS__))
#define MAKE_ARG_LIST_31(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_30(op, __VA_ARGS__))
#define MAKE_ARG_LIST_32(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_31(op, __VA_ARGS__))
#define MAKE_ARG_LIST_33(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_32(op, __VA_ARGS__))
#define MAKE_ARG_LIST_34(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_33(op, __VA_ARGS__))
#define MAKE_ARG_LIST_35(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_34(op, __VA_ARGS__))
#define MAKE_ARG_LIST_36(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_35(op, __VA_ARGS__))
#define MAKE_ARG_LIST_37(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_36(op, __VA_ARGS__))
#define MAKE_ARG_LIST_38(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_37(op, __VA_ARGS__))
#define MAKE_ARG_LIST_39(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_38(op, __VA_ARGS__))
#define MAKE_ARG_LIST_40(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_39(op, __VA_ARGS__))
#define MAKE_ARG_LIST_41(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_40(op, __VA_ARGS__))
#define MAKE_ARG_LIST_42(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_41(op, __VA_ARGS__))
#define MAKE_ARG_LIST_43(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_42(op, __VA_ARGS__))
#define MAKE_ARG_LIST_44(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_43(op, __VA_ARGS__))
#define MAKE_ARG_LIST_45(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_44(op, __VA_ARGS__))
#define MAKE_ARG_LIST_46(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_45(op, __VA_ARGS__))
#define MAKE_ARG_LIST_47(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_46(op, __VA_ARGS__))
#define MAKE_ARG_LIST_48(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_47(op, __VA_ARGS__))
#define MAKE_ARG_LIST_49(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_48(op, __VA_ARGS__))
#define MAKE_ARG_LIST_50(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_49(op, __VA_ARGS__))
#define MAKE_ARG_LIST_51(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_50(op, __VA_ARGS__))
#define MAKE_ARG_LIST_52(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_51(op, __VA_ARGS__))
#define MAKE_ARG_LIST_53(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_52(op, __VA_ARGS__))
#define MAKE_ARG_LIST_54(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_53(op, __VA_ARGS__))
#define MAKE_ARG_LIST_55(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_54(op, __VA_ARGS__))
#define MAKE_ARG_LIST_56(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_55(op, __VA_ARGS__))
#define MAKE_ARG_LIST_57(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_56(op, __VA_ARGS__))
#define MAKE_ARG_LIST_58(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_57(op, __VA_ARGS__))
#define MAKE_ARG_LIST_59(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_58(op, __VA_ARGS__))
#define MAKE_ARG_LIST_60(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_59(op, __VA_ARGS__))
#define MAKE_ARG_LIST_61(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_60(op, __VA_ARGS__))
#define MAKE_ARG_LIST_62(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_61(op, __VA_ARGS__))
#define MAKE_ARG_LIST_63(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_62(op, __VA_ARGS__))
#define MAKE_ARG_LIST_64(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_63(op, __VA_ARGS__))
#define MAKE_ARG_LIST_65(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_64(op, __VA_ARGS__))
#define MAKE_ARG_LIST_66(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_65(op, __VA_ARGS__))
#define MAKE_ARG_LIST_67(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_66(op, __VA_ARGS__))
#define MAKE_ARG_LIST_68(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_67(op, __VA_ARGS__))
#define MAKE_ARG_LIST_69(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_68(op, __VA_ARGS__))
#define MAKE_ARG_LIST_70(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_69(op, __VA_ARGS__))
#define MAKE_ARG_LIST_71(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_70(op, __VA_ARGS__))
#define MAKE_ARG_LIST_72(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_71(op, __VA_ARGS__))
#define MAKE_ARG_LIST_73(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_72(op, __VA_ARGS__))
#define MAKE_ARG_LIST_74(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_73(op, __VA_ARGS__))
#define MAKE_ARG_LIST_75(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_74(op, __VA_ARGS__))
#define MAKE_ARG_LIST_76(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_75(op, __VA_ARGS__))
#define MAKE_ARG_LIST_77(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_76(op, __VA_ARGS__))
#define MAKE_ARG_LIST_78(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_77(op, __VA_ARGS__))
#define MAKE_ARG_LIST_79(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_78(op, __VA_ARGS__))
#define MAKE_ARG_LIST_80(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_79(op, __VA_ARGS__))
#define MAKE_ARG_LIST_81(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_80(op, __VA_ARGS__))
#define MAKE_ARG_LIST_82(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_81(op, __VA_ARGS__))
#define MAKE_ARG_LIST_83(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_82(op, __VA_ARGS__))
#define MAKE_ARG_LIST_84(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_83(op, __VA_ARGS__))
#define MAKE_ARG_LIST_85(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_84(op, __VA_ARGS__))
#define MAKE_ARG_LIST_86(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_85(op, __VA_ARGS__))
#define MAKE_ARG_LIST_87(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_86(op, __VA_ARGS__))
#define MAKE_ARG_LIST_88(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_87(op, __VA_ARGS__))
#define MAKE_ARG_LIST_89(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_88(op, __VA_ARGS__))
#define MAKE_ARG_LIST_90(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_89(op, __VA_ARGS__))
#define MAKE_ARG_LIST_91(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_90(op, __VA_ARGS__))
#define MAKE_ARG_LIST_92(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_91(op, __VA_ARGS__))
#define MAKE_ARG_LIST_93(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_92(op, __VA_ARGS__))
#define MAKE_ARG_LIST_94(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_93(op, __VA_ARGS__))
#define MAKE_ARG_LIST_95(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_94(op, __VA_ARGS__))
#define MAKE_ARG_LIST_96(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_95(op, __VA_ARGS__))
#define MAKE_ARG_LIST_97(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_96(op, __VA_ARGS__))
#define MAKE_ARG_LIST_98(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_97(op, __VA_ARGS__))
#define MAKE_ARG_LIST_99(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_98(op, __VA_ARGS__))
#define MAKE_ARG_LIST_100(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_99(op, __VA_ARGS__))
#define MAKE_ARG_LIST_101(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_100(op, __VA_ARGS__))
#define MAKE_ARG_LIST_102(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_101(op, __VA_ARGS__))
#define MAKE_ARG_LIST_103(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_102(op, __VA_ARGS__))
#define MAKE_ARG_LIST_104(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_103(op, __VA_ARGS__))
#define MAKE_ARG_LIST_105(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_104(op, __VA_ARGS__))
#define MAKE_ARG_LIST_106(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_105(op, __VA_ARGS__))
#define MAKE_ARG_LIST_107(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_106(op, __VA_ARGS__))
#define MAKE_ARG_LIST_108(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_107(op, __VA_ARGS__))
#define MAKE_ARG_LIST_109(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_108(op, __VA_ARGS__))
#define MAKE_ARG_LIST_110(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_109(op, __VA_ARGS__))
#define MAKE_ARG_LIST_111(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_110(op, __VA_ARGS__))
#define MAKE_ARG_LIST_112(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_111(op, __VA_ARGS__))
#define MAKE_ARG_LIST_113(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_112(op, __VA_ARGS__))
#define MAKE_ARG_LIST_114(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_113(op, __VA_ARGS__))
#define MAKE_ARG_LIST_115(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_114(op, __VA_ARGS__))
#define MAKE_ARG_LIST_116(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_115(op, __VA_ARGS__))
#define MAKE_ARG_LIST_117(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_116(op, __VA_ARGS__))
#define MAKE_ARG_LIST_118(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_117(op, __VA_ARGS__))
#define MAKE_ARG_LIST_119(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_118(op, __VA_ARGS__))
#define MAKE_ARG_LIST_120(op, arg, ...) \
  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_119(op, __VA_ARGS__))

#define ADD_VIEW(str) std::string_view(#str, sizeof(#str) - 1)

#define SEPERATOR ,
#define CON_STR_1(element, ...) ADD_VIEW(element)
#define CON_STR_2(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_1(__VA_ARGS__))
#define CON_STR_3(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_2(__VA_ARGS__))
#define CON_STR_4(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_3(__VA_ARGS__))
#define CON_STR_5(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_4(__VA_ARGS__))
#define CON_STR_6(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_5(__VA_ARGS__))
#define CON_STR_7(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_6(__VA_ARGS__))
#define CON_STR_8(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_7(__VA_ARGS__))
#define CON_STR_9(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_8(__VA_ARGS__))
#define CON_STR_10(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_9(__VA_ARGS__))
#define CON_STR_11(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_10(__VA_ARGS__))
#define CON_STR_12(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_11(__VA_ARGS__))
#define CON_STR_13(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_12(__VA_ARGS__))
#define CON_STR_14(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_13(__VA_ARGS__))
#define CON_STR_15(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_14(__VA_ARGS__))
#define CON_STR_16(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_15(__VA_ARGS__))
#define CON_STR_17(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_16(__VA_ARGS__))
#define CON_STR_18(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_17(__VA_ARGS__))
#define CON_STR_19(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_18(__VA_ARGS__))
#define CON_STR_20(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_19(__VA_ARGS__))
#define CON_STR_21(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_20(__VA_ARGS__))
#define CON_STR_22(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_21(__VA_ARGS__))
#define CON_STR_23(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_22(__VA_ARGS__))
#define CON_STR_24(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_23(__VA_ARGS__))
#define CON_STR_25(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_24(__VA_ARGS__))
#define CON_STR_26(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_25(__VA_ARGS__))
#define CON_STR_27(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_26(__VA_ARGS__))
#define CON_STR_28(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_27(__VA_ARGS__))
#define CON_STR_29(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_28(__VA_ARGS__))
#define CON_STR_30(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_29(__VA_ARGS__))
#define CON_STR_31(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_30(__VA_ARGS__))
#define CON_STR_32(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_31(__VA_ARGS__))
#define CON_STR_33(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_32(__VA_ARGS__))
#define CON_STR_34(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_33(__VA_ARGS__))
#define CON_STR_35(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_34(__VA_ARGS__))
#define CON_STR_36(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_35(__VA_ARGS__))
#define CON_STR_37(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_36(__VA_ARGS__))
#define CON_STR_38(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_37(__VA_ARGS__))
#define CON_STR_39(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_38(__VA_ARGS__))
#define CON_STR_40(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_39(__VA_ARGS__))
#define CON_STR_41(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_40(__VA_ARGS__))
#define CON_STR_42(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_41(__VA_ARGS__))
#define CON_STR_43(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_42(__VA_ARGS__))
#define CON_STR_44(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_43(__VA_ARGS__))
#define CON_STR_45(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_44(__VA_ARGS__))
#define CON_STR_46(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_45(__VA_ARGS__))
#define CON_STR_47(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_46(__VA_ARGS__))
#define CON_STR_48(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_47(__VA_ARGS__))
#define CON_STR_49(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_48(__VA_ARGS__))
#define CON_STR_50(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_49(__VA_ARGS__))
#define CON_STR_51(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_50(__VA_ARGS__))
#define CON_STR_52(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_51(__VA_ARGS__))
#define CON_STR_53(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_52(__VA_ARGS__))
#define CON_STR_54(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_53(__VA_ARGS__))
#define CON_STR_55(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_54(__VA_ARGS__))
#define CON_STR_56(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_55(__VA_ARGS__))
#define CON_STR_57(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_56(__VA_ARGS__))
#define CON_STR_58(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_57(__VA_ARGS__))
#define CON_STR_59(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_58(__VA_ARGS__))
#define CON_STR_60(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_59(__VA_ARGS__))
#define CON_STR_61(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_60(__VA_ARGS__))
#define CON_STR_62(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_61(__VA_ARGS__))
#define CON_STR_63(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_62(__VA_ARGS__))
#define CON_STR_64(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_63(__VA_ARGS__))
#define CON_STR_65(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_64(__VA_ARGS__))
#define CON_STR_66(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_65(__VA_ARGS__))
#define CON_STR_67(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_66(__VA_ARGS__))
#define CON_STR_68(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_67(__VA_ARGS__))
#define CON_STR_69(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_68(__VA_ARGS__))
#define CON_STR_70(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_69(__VA_ARGS__))
#define CON_STR_71(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_70(__VA_ARGS__))
#define CON_STR_72(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_71(__VA_ARGS__))
#define CON_STR_73(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_72(__VA_ARGS__))
#define CON_STR_74(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_73(__VA_ARGS__))
#define CON_STR_75(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_74(__VA_ARGS__))
#define CON_STR_76(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_75(__VA_ARGS__))
#define CON_STR_77(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_76(__VA_ARGS__))
#define CON_STR_78(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_77(__VA_ARGS__))
#define CON_STR_79(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_78(__VA_ARGS__))
#define CON_STR_80(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_79(__VA_ARGS__))
#define CON_STR_81(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_80(__VA_ARGS__))
#define CON_STR_82(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_81(__VA_ARGS__))
#define CON_STR_83(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_82(__VA_ARGS__))
#define CON_STR_84(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_83(__VA_ARGS__))
#define CON_STR_85(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_84(__VA_ARGS__))
#define CON_STR_86(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_85(__VA_ARGS__))
#define CON_STR_87(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_86(__VA_ARGS__))
#define CON_STR_88(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_87(__VA_ARGS__))
#define CON_STR_89(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_88(__VA_ARGS__))
#define CON_STR_90(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_89(__VA_ARGS__))
#define CON_STR_91(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_90(__VA_ARGS__))
#define CON_STR_92(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_91(__VA_ARGS__))
#define CON_STR_93(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_92(__VA_ARGS__))
#define CON_STR_94(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_93(__VA_ARGS__))
#define CON_STR_95(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_94(__VA_ARGS__))
#define CON_STR_96(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_95(__VA_ARGS__))
#define CON_STR_97(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_96(__VA_ARGS__))
#define CON_STR_98(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_97(__VA_ARGS__))
#define CON_STR_99(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_98(__VA_ARGS__))
#define CON_STR_100(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_99(__VA_ARGS__))
#define CON_STR_101(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_100(__VA_ARGS__))
#define CON_STR_102(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_101(__VA_ARGS__))
#define CON_STR_103(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_102(__VA_ARGS__))
#define CON_STR_104(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_103(__VA_ARGS__))
#define CON_STR_105(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_104(__VA_ARGS__))
#define CON_STR_106(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_105(__VA_ARGS__))
#define CON_STR_107(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_106(__VA_ARGS__))
#define CON_STR_108(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_107(__VA_ARGS__))
#define CON_STR_109(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_108(__VA_ARGS__))
#define CON_STR_110(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_109(__VA_ARGS__))
#define CON_STR_111(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_110(__VA_ARGS__))
#define CON_STR_112(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_111(__VA_ARGS__))
#define CON_STR_113(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_112(__VA_ARGS__))
#define CON_STR_114(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_113(__VA_ARGS__))
#define CON_STR_115(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_114(__VA_ARGS__))
#define CON_STR_116(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_115(__VA_ARGS__))
#define CON_STR_117(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_116(__VA_ARGS__))
#define CON_STR_118(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_117(__VA_ARGS__))
#define CON_STR_119(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_118(__VA_ARGS__))
#define CON_STR_120(element, ...) \
  ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_119(__VA_ARGS__))
#define RSEQ_N()                                                               \
  119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105,   \
      104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, \
      87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70,  \
      69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52,  \
      51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34,  \
      33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  \
      15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,     \
              _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
              _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
              _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, \
              _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, \
              _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, \
              _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, \
              _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, \
              _105, _106, _107, _108, _109, _110, _111, _112, _113, _114,      \
              _115, _116, _117, _118, _119, N, ...)                            \
  N

#define MARCO_EXPAND(...) __VA_ARGS__
#define APPLY_VARIADIC_MACRO(macro, ...) MARCO_EXPAND(macro(__VA_ARGS__))

#define FIELD(t) t
#define FIELD_STR(t) #t
#define MAKE_NAMES(...) #__VA_ARGS__

// note use MACRO_CONCAT like A##_##B direct may cause marco expand error
#define MACRO_CONCAT(A, B) MACRO_CONCAT1(A, B)
#define MACRO_CONCAT1(A, B) A##_##B

#define MAKE_ARG_LIST(N, op, arg, ...) \
  MACRO_CONCAT(MAKE_ARG_LIST, N)(op, arg, __VA_ARGS__)

#define GET_ARG_COUNT_INNER(...) MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...) GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define MAKE_STR_LIST(...) \
  MACRO_CONCAT(CON_STR, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define MAKE_META_DATA_IMPL(STRUCT_NAME, KEY_INDEX, N, ...)                                       \
    inline auto iguana_reflect_members(STRUCT_NAME const&) {                                      \
        struct reflect_members {                                                                  \
            constexpr decltype(auto) static apply_impl() {                                        \
                return std::make_tuple(MAKE_ARG_LIST(N, &STRUCT_NAME::FIELD, __VA_ARGS__));       \
            }                                                                                     \
            constexpr static std::size_t size() {                                                 \
                return std::integral_constant<std::size_t, GET_ARG_COUNT(__VA_ARGS__)>::value;    \
            }                                                                                     \
            constexpr static std::string_view fields() { return MAKE_NAMES(__VA_ARGS__); }        \
            constexpr decltype(auto) static field_index() {                                       \
                return std::make_tuple(MAKE_ARG_LIST(N, FIELD_STR, __VA_ARGS__));                 \
            }                                                                                     \
            constexpr static std::string_view name() { return #STRUCT_NAME; }                     \
            constexpr static std::size_t key_index() {                                            \
                return std::integral_constant<std::size_t, KEY_INDEX>::value;                     \
            }                                                                                     \
        };                                                                                        \
        return reflect_members{};                                                                 \
    }

#define MAKE_META_DATA(STRUCT_NAME, KEY_INDEX, N, ...)                 \
  MAKE_META_DATA_IMPL(STRUCT_NAME, KEY_INDEX, N, __VA_ARGS__)

#define REFLECTION(STRUCT_NAME, KEY_INDEX, ...)                        \
  MAKE_META_DATA(STRUCT_NAME, KEY_INDEX, GET_ARG_COUNT(__VA_ARGS__),   \
                 __VA_ARGS__)

//#define REFLECTION_WITH_NAME(STRUCT_NAME, TABLE_NAME, ...)            \
//  MAKE_META_DATA(STRUCT_NAME, TABLE_NAME, GET_ARG_COUNT(__VA_ARGS__), \
//                 __VA_ARGS__)



#define VARCHAR_STR1 "VARCHAR("
#define VARCHAR_STR2(N) #N
#define VARCHAR_STR3 ")"sv

#define VARCHAR_STR(N) VARCHAR_STR1 VARCHAR_STR2(N) VARCHAR_STR3

#define GET_VARCHAR_STR                                                                             \
    static_assert((N & (N - 1)) == 0, "not support the such of array, array size must be 2^N");     \
    if constexpr (N == 2) { return VARCHAR_STR(2); }                                                \
    else if constexpr (N == 4) { return VARCHAR_STR(4); }                                           \
    else if constexpr (N == 8) { return VARCHAR_STR(8); }                                           \
    else if constexpr (N == 16) { return VARCHAR_STR(16); }                                         \
    else if constexpr (N == 32) { return VARCHAR_STR(32); }                                         \
    else if constexpr (N == 64) { return VARCHAR_STR(64); }                                         \
    else if constexpr (N == 128) { return VARCHAR_STR(128); }                                       \
    else if constexpr (N == 256) { return VARCHAR_STR(256); }                                       \
    else { return "VARCHAR(256)"sv; }


    //else if constexpr (N == 3) { return VARCHAR_STR(3)sv; }         \

    //else if constexpr (N == 5) { return VARCHAR_STR(5)sv; }         \
    //else if constexpr (N == 6) { return VARCHAR_STR(6)sv; }         \
    //else if constexpr (N == 7) { return VARCHAR_STR(7)sv; }         \

    //else if constexpr (N == 9) { return VARCHAR_STR(9)sv; }         \
    //else if constexpr (N == 10) { return VARCHAR_STR(10)sv; }       \
    //else if constexpr (N == 11) { return VARCHAR_STR(11)sv; }       \
    //else if constexpr (N == 12) { return VARCHAR_STR(12)sv; }       \
    //else if constexpr (N == 13) { return VARCHAR_STR(13)sv; }       \
    //else if constexpr (N == 14) { return VARCHAR_STR(14)sv; }       \
    //else if constexpr (N == 15) { return VARCHAR_STR(15)sv; }       \

    //else if constexpr (N == 17) { return VARCHAR_STR(17)sv; }       \
    //else if constexpr (N == 18) { return VARCHAR_STR(18)sv; }       \
    //else if constexpr (N == 19) { return VARCHAR_STR(19)sv; }       \
    //else if constexpr (N == 20) { return VARCHAR_STR(20)sv; }       \
    //else if constexpr (N == 21) { return VARCHAR_STR(21)sv; }       \
    //else if constexpr (N == 22) { return VARCHAR_STR(22)sv; }       \
    //else if constexpr (N == 23) { return VARCHAR_STR(23)sv; }       \
    //else if constexpr (N == 24) { return VARCHAR_STR(24)sv; }       \
    //else if constexpr (N == 25) { return VARCHAR_STR(25)sv; }       \
    //else if constexpr (N == 26) { return VARCHAR_STR(26)sv; }       \
    //else if constexpr (N == 27) { return VARCHAR_STR(27)sv; }       \
    //else if constexpr (N == 28) { return VARCHAR_STR(28)sv; }       \
    //else if constexpr (N == 29) { return VARCHAR_STR(29)sv; }       \
    //else if constexpr (N == 30) { return VARCHAR_STR(30)sv; }       \
    //else if constexpr (N == 31) { return VARCHAR_STR(31)sv; }       \

    //else if constexpr (N == 33) { return VARCHAR_STR(33)sv; }       \
    //else if constexpr (N == 34) { return VARCHAR_STR(34)sv; }       \
    //else if constexpr (N == 35) { return VARCHAR_STR(35)sv; }       \
    //else if constexpr (N == 36) { return VARCHAR_STR(36)sv; }       \
    //else if constexpr (N == 37) { return VARCHAR_STR(37)sv; }       \
    //else if constexpr (N == 38) { return VARCHAR_STR(38)sv; }       \
    //else if constexpr (N == 39) { return VARCHAR_STR(39)sv; }       \
    //else if constexpr (N == 40) { return VARCHAR_STR(30)sv; }       \
    //else if constexpr (N == 41) { return VARCHAR_STR(41)sv; }       \
    //else if constexpr (N == 42) { return VARCHAR_STR(42)sv; }       \
    //else if constexpr (N == 43) { return VARCHAR_STR(43)sv; }       \
    //else if constexpr (N == 44) { return VARCHAR_STR(44)sv; }       \
    //else if constexpr (N == 45) { return VARCHAR_STR(45)sv; }       \
    //else if constexpr (N == 46) { return VARCHAR_STR(46)sv; }       \
    //else if constexpr (N == 47) { return VARCHAR_STR(47)sv; }       \
    //else if constexpr (N == 48) { return VARCHAR_STR(48)sv; }       \
    //else if constexpr (N == 49) { return VARCHAR_STR(49)sv; }       \
    //else if constexpr (N == 50) { return VARCHAR_STR(50)sv; }       \
    //else if constexpr (N == 51) { return VARCHAR_STR(51)sv; }       \
    //else if constexpr (N == 52) { return VARCHAR_STR(52)sv; }       \
    //else if constexpr (N == 53) { return VARCHAR_STR(53)sv; }       \
    //else if constexpr (N == 54) { return VARCHAR_STR(54)sv; }       \
    //else if constexpr (N == 55) { return VARCHAR_STR(55)sv; }       \
    //else if constexpr (N == 56) { return VARCHAR_STR(56)sv; }       \
    //else if constexpr (N == 57) { return VARCHAR_STR(57)sv; }       \
    //else if constexpr (N == 58) { return VARCHAR_STR(58)sv; }       \
    //else if constexpr (N == 59) { return VARCHAR_STR(59)sv; }       \
    //else if constexpr (N == 60) { return VARCHAR_STR(60)sv; }       \
    //else if constexpr (N == 61) { return VARCHAR_STR(61)sv; }       \
    //else if constexpr (N == 62) { return VARCHAR_STR(62)sv; }       \
    //else if constexpr (N == 63) { return VARCHAR_STR(63)sv; }       \

    //else if constexpr (N == 65) { return VARCHAR_STR(65)sv; }       \
    //else if constexpr (N == 66) { return VARCHAR_STR(66)sv; }       \
    //else if constexpr (N == 67) { return VARCHAR_STR(67)sv; }       \
    //else if constexpr (N == 68) { return VARCHAR_STR(68)sv; }       \
    //else if constexpr (N == 69) { return VARCHAR_STR(69)sv; }       \
    //else if constexpr (N == 70) { return VARCHAR_STR(30)sv; }       \
    //else if constexpr (N == 71) { return VARCHAR_STR(71)sv; }       \
    //else if constexpr (N == 72) { return VARCHAR_STR(72)sv; }       \
    //else if constexpr (N == 73) { return VARCHAR_STR(73)sv; }       \
    //else if constexpr (N == 74) { return VARCHAR_STR(74)sv; }       \
    //else if constexpr (N == 75) { return VARCHAR_STR(75)sv; }       \
    //else if constexpr (N == 76) { return VARCHAR_STR(76)sv; }       \
    //else if constexpr (N == 77) { return VARCHAR_STR(77)sv; }       \
    //else if constexpr (N == 78) { return VARCHAR_STR(78)sv; }       \
    //else if constexpr (N == 79) { return VARCHAR_STR(79)sv; }       \
    //else if constexpr (N == 80) { return VARCHAR_STR(80)sv; }       \
    //else if constexpr (N == 81) { return VARCHAR_STR(81)sv; }       \
    //else if constexpr (N == 82) { return VARCHAR_STR(82)sv; }       \
    //else if constexpr (N == 83) { return VARCHAR_STR(83)sv; }       \
    //else if constexpr (N == 84) { return VARCHAR_STR(84)sv; }       \
    //else if constexpr (N == 85) { return VARCHAR_STR(85)sv; }       \
    //else if constexpr (N == 86) { return VARCHAR_STR(86)sv; }       \
    //else if constexpr (N == 87) { return VARCHAR_STR(87)sv; }       \
    //else if constexpr (N == 88) { return VARCHAR_STR(88)sv; }       \
    //else if constexpr (N == 89) { return VARCHAR_STR(89)sv; }       \
    //else if constexpr (N == 90) { return VARCHAR_STR(90)sv; }       \
    //else if constexpr (N == 91) { return VARCHAR_STR(91)sv; }       \
    //else if constexpr (N == 92) { return VARCHAR_STR(92)sv; }       \
    //else if constexpr (N == 93) { return VARCHAR_STR(93)sv; }       \
    //else if constexpr (N == 94) { return VARCHAR_STR(94)sv; }       \
    //else if constexpr (N == 95) { return VARCHAR_STR(95)sv; }       \
    //else if constexpr (N == 96) { return VARCHAR_STR(96)sv; }       \
    //else if constexpr (N == 97) { return VARCHAR_STR(97)sv; }       \
    //else if constexpr (N == 98) { return VARCHAR_STR(98)sv; }       \
    //else if constexpr (N == 99) { return VARCHAR_STR(99)sv; }       \
    //else if constexpr (N == 101) { return VARCHAR_STR(101)sv; }     \
    //else if constexpr (N == 102) { return VARCHAR_STR(102)sv; }     \
    //else if constexpr (N == 103) { return VARCHAR_STR(103)sv; }     \
    //else if constexpr (N == 104) { return VARCHAR_STR(104)sv; }     \
    //else if constexpr (N == 105) { return VARCHAR_STR(105)sv; }     \
    //else if constexpr (N == 106) { return VARCHAR_STR(106)sv; }     \
    //else if constexpr (N == 107) { return VARCHAR_STR(107)sv; }     \
    //else if constexpr (N == 108) { return VARCHAR_STR(108)sv; }     \
    //else if constexpr (N == 109) { return VARCHAR_STR(109)sv; }     \
    //else if constexpr (N == 110) { return VARCHAR_STR(110)sv; }     \
    //else if constexpr (N == 111) { return VARCHAR_STR(111)sv; }     \
    //else if constexpr (N == 112) { return VARCHAR_STR(112)sv; }     \
    //else if constexpr (N == 113) { return VARCHAR_STR(113)sv; }     \
    //else if constexpr (N == 114) { return VARCHAR_STR(114)sv; }     \
    //else if constexpr (N == 115) { return VARCHAR_STR(115)sv; }     \
    //else if constexpr (N == 116) { return VARCHAR_STR(116)sv; }     \
    //else if constexpr (N == 117) { return VARCHAR_STR(117)sv; }     \
    //else if constexpr (N == 118) { return VARCHAR_STR(118)sv; }     \
    //else if constexpr (N == 119) { return VARCHAR_STR(119)sv; }     \
    //else if constexpr (N == 120) { return VARCHAR_STR(120)sv; }     \
    //else if constexpr (N == 121) { return VARCHAR_STR(121)sv; }     \
    //else if constexpr (N == 122) { return VARCHAR_STR(122)sv; }     \
    //else if constexpr (N == 123) { return VARCHAR_STR(123)sv; }     \
    //else if constexpr (N == 124) { return VARCHAR_STR(124)sv; }     \
    //else if constexpr (N == 125) { return VARCHAR_STR(125)sv; }     \
    //else if constexpr (N == 126) { return VARCHAR_STR(126)sv; }     \
    //else if constexpr (N == 127) { return VARCHAR_STR(127)sv; }     \

    //else if constexpr (N == 129) { return VARCHAR_STR(129)sv; }     \
    //else if constexpr (N == 130) { return VARCHAR_STR(130)sv; }     \
    //else if constexpr (N == 131) { return VARCHAR_STR(131)sv; }     \
    //else if constexpr (N == 132) { return VARCHAR_STR(132)sv; }     \
    //else if constexpr (N == 133) { return VARCHAR_STR(133)sv; }     \
    //else if constexpr (N == 134) { return VARCHAR_STR(134)sv; }     \
    //else if constexpr (N == 135) { return VARCHAR_STR(135)sv; }     \
    //else if constexpr (N == 136) { return VARCHAR_STR(136)sv; }     \
    //else if constexpr (N == 137) { return VARCHAR_STR(137)sv; }     \
    //else if constexpr (N == 138) { return VARCHAR_STR(138)sv; }     \
    //else if constexpr (N == 139) { return VARCHAR_STR(139)sv; }     \
    //else if constexpr (N == 140) { return VARCHAR_STR(140)sv; }     \
    //else if constexpr (N == 141) { return VARCHAR_STR(141)sv; }     \
    //else if constexpr (N == 142) { return VARCHAR_STR(142)sv; }     \
    //else if constexpr (N == 143) { return VARCHAR_STR(143)sv; }     \
    //else if constexpr (N == 144) { return VARCHAR_STR(144)sv; }     \
    //else if constexpr (N == 145) { return VARCHAR_STR(145)sv; }     \
    //else if constexpr (N == 146) { return VARCHAR_STR(146)sv; }     \
    //else if constexpr (N == 147) { return VARCHAR_STR(147)sv; }     \
    //else if constexpr (N == 148) { return VARCHAR_STR(148)sv; }     \
    //else if constexpr (N == 149) { return VARCHAR_STR(149)sv; }     \
    //else if constexpr (N == 150) { return VARCHAR_STR(150)sv; }     \
    //else if constexpr (N == 151) { return VARCHAR_STR(151)sv; }     \
    //else if constexpr (N == 152) { return VARCHAR_STR(152)sv; }     \
    //else if constexpr (N == 153) { return VARCHAR_STR(153)sv; }     \
    //else if constexpr (N == 154) { return VARCHAR_STR(154)sv; }     \
    //else if constexpr (N == 155) { return VARCHAR_STR(155)sv; }     \
    //else if constexpr (N == 156) { return VARCHAR_STR(156)sv; }     \
    //else if constexpr (N == 157) { return VARCHAR_STR(157)sv; }     \
    //else if constexpr (N == 158) { return VARCHAR_STR(158)sv; }     \
    //else if constexpr (N == 159) { return VARCHAR_STR(159)sv; }     \
    //else if constexpr (N == 160) { return VARCHAR_STR(160)sv; }     \
    //else if constexpr (N == 161) { return VARCHAR_STR(161)sv; }     \
    //else if constexpr (N == 162) { return VARCHAR_STR(162)sv; }     \
    //else if constexpr (N == 163) { return VARCHAR_STR(163)sv; }     \
    //else if constexpr (N == 164) { return VARCHAR_STR(164)sv; }     \
    //else if constexpr (N == 165) { return VARCHAR_STR(165)sv; }     \
    //else if constexpr (N == 166) { return VARCHAR_STR(166)sv; }     \
    //else if constexpr (N == 167) { return VARCHAR_STR(167)sv; }     \
    //else if constexpr (N == 168) { return VARCHAR_STR(168)sv; }     \
    //else if constexpr (N == 169) { return VARCHAR_STR(169)sv; }     \
    //else if constexpr (N == 170) { return VARCHAR_STR(170)sv; }     \
    //else if constexpr (N == 171) { return VARCHAR_STR(171)sv; }     \
    //else if constexpr (N == 172) { return VARCHAR_STR(172)sv; }     \
    //else if constexpr (N == 173) { return VARCHAR_STR(173)sv; }     \
    //else if constexpr (N == 174) { return VARCHAR_STR(174)sv; }     \
    //else if constexpr (N == 175) { return VARCHAR_STR(175)sv; }     \
    //else if constexpr (N == 176) { return VARCHAR_STR(176)sv; }     \
    //else if constexpr (N == 177) { return VARCHAR_STR(177)sv; }     \
    //else if constexpr (N == 178) { return VARCHAR_STR(178)sv; }     \
    //else if constexpr (N == 179) { return VARCHAR_STR(179)sv; }     \
    //else if constexpr (N == 180) { return VARCHAR_STR(180)sv; }     \
    //else if constexpr (N == 181) { return VARCHAR_STR(181)sv; }     \
    //else if constexpr (N == 182) { return VARCHAR_STR(182)sv; }     \
    //else if constexpr (N == 183) { return VARCHAR_STR(183)sv; }     \
    //else if constexpr (N == 184) { return VARCHAR_STR(184)sv; }     \
    //else if constexpr (N == 185) { return VARCHAR_STR(185)sv; }     \
    //else if constexpr (N == 186) { return VARCHAR_STR(186)sv; }     \
    //else if constexpr (N == 187) { return VARCHAR_STR(187)sv; }     \
    //else if constexpr (N == 188) { return VARCHAR_STR(188)sv; }     \
    //else if constexpr (N == 189) { return VARCHAR_STR(189)sv; }     \
    //else if constexpr (N == 190) { return VARCHAR_STR(190)sv; }     \
    //else if constexpr (N == 191) { return VARCHAR_STR(191)sv; }     \
    //else if constexpr (N == 192) { return VARCHAR_STR(192)sv; }     \
    //else if constexpr (N == 193) { return VARCHAR_STR(193)sv; }     \
    //else if constexpr (N == 194) { return VARCHAR_STR(194)sv; }     \
    //else if constexpr (N == 195) { return VARCHAR_STR(195)sv; }     \
    //else if constexpr (N == 196) { return VARCHAR_STR(196)sv; }     \
    //else if constexpr (N == 197) { return VARCHAR_STR(197)sv; }     \
    //else if constexpr (N == 198) { return VARCHAR_STR(198)sv; }     \
    //else if constexpr (N == 199) { return VARCHAR_STR(199)sv; }     \
    //else if constexpr (N == 201) { return VARCHAR_STR(201)sv; }     \
    //else if constexpr (N == 202) { return VARCHAR_STR(202)sv; }     \
    //else if constexpr (N == 203) { return VARCHAR_STR(203)sv; }     \
    //else if constexpr (N == 204) { return VARCHAR_STR(204)sv; }     \
    //else if constexpr (N == 205) { return VARCHAR_STR(205)sv; }     \
    //else if constexpr (N == 206) { return VARCHAR_STR(206)sv; }     \
    //else if constexpr (N == 207) { return VARCHAR_STR(207)sv; }     \
    //else if constexpr (N == 208) { return VARCHAR_STR(208)sv; }     \
    //else if constexpr (N == 209) { return VARCHAR_STR(209)sv; }     \
    //else if constexpr (N == 210) { return VARCHAR_STR(210)sv; }     \
    //else if constexpr (N == 211) { return VARCHAR_STR(211)sv; }     \
    //else if constexpr (N == 212) { return VARCHAR_STR(212)sv; }     \
    //else if constexpr (N == 213) { return VARCHAR_STR(213)sv; }     \
    //else if constexpr (N == 214) { return VARCHAR_STR(214)sv; }     \
    //else if constexpr (N == 215) { return VARCHAR_STR(215)sv; }     \
    //else if constexpr (N == 216) { return VARCHAR_STR(216)sv; }     \
    //else if constexpr (N == 217) { return VARCHAR_STR(217)sv; }     \
    //else if constexpr (N == 218) { return VARCHAR_STR(218)sv; }     \
    //else if constexpr (N == 219) { return VARCHAR_STR(219)sv; }     \
    //else if constexpr (N == 220) { return VARCHAR_STR(220)sv; }     \
    //else if constexpr (N == 221) { return VARCHAR_STR(221)sv; }     \
    //else if constexpr (N == 222) { return VARCHAR_STR(222)sv; }     \
    //else if constexpr (N == 223) { return VARCHAR_STR(223)sv; }     \
    //else if constexpr (N == 224) { return VARCHAR_STR(224)sv; }     \
    //else if constexpr (N == 225) { return VARCHAR_STR(225)sv; }     \
    //else if constexpr (N == 226) { return VARCHAR_STR(226)sv; }     \
    //else if constexpr (N == 227) { return VARCHAR_STR(227)sv; }     \
    //else if constexpr (N == 228) { return VARCHAR_STR(228)sv; }     \
    //else if constexpr (N == 229) { return VARCHAR_STR(229)sv; }     \
    //else if constexpr (N == 230) { return VARCHAR_STR(230)sv; }     \
    //else if constexpr (N == 231) { return VARCHAR_STR(231)sv; }     \
    //else if constexpr (N == 232) { return VARCHAR_STR(232)sv; }     \
    //else if constexpr (N == 233) { return VARCHAR_STR(233)sv; }     \
    //else if constexpr (N == 234) { return VARCHAR_STR(234)sv; }     \
    //else if constexpr (N == 235) { return VARCHAR_STR(235)sv; }     \
    //else if constexpr (N == 236) { return VARCHAR_STR(236)sv; }     \
    //else if constexpr (N == 237) { return VARCHAR_STR(237)sv; }     \
    //else if constexpr (N == 238) { return VARCHAR_STR(238)sv; }     \
    //else if constexpr (N == 239) { return VARCHAR_STR(239)sv; }     \
    //else if constexpr (N == 240) { return VARCHAR_STR(230)sv; }     \
    //else if constexpr (N == 241) { return VARCHAR_STR(241)sv; }     \
    //else if constexpr (N == 242) { return VARCHAR_STR(242)sv; }     \
    //else if constexpr (N == 243) { return VARCHAR_STR(243)sv; }     \
    //else if constexpr (N == 244) { return VARCHAR_STR(244)sv; }     \
    //else if constexpr (N == 245) { return VARCHAR_STR(245)sv; }     \
    //else if constexpr (N == 246) { return VARCHAR_STR(246)sv; }     \
    //else if constexpr (N == 247) { return VARCHAR_STR(247)sv; }     \
    //else if constexpr (N == 248) { return VARCHAR_STR(248)sv; }     \
    //else if constexpr (N == 249) { return VARCHAR_STR(249)sv; }     \
    //else if constexpr (N == 250) { return VARCHAR_STR(250)sv; }     \
    //else if constexpr (N == 251) { return VARCHAR_STR(251)sv; }     \
    //else if constexpr (N == 252) { return VARCHAR_STR(252)sv; }     \
    //else if constexpr (N == 253) { return VARCHAR_STR(253)sv; }     \
    //else if constexpr (N == 254) { return VARCHAR_STR(254)sv; }     \
    //else if constexpr (N == 255) { return VARCHAR_STR(255)sv; }     \

#endif  // LLM_REFLECTION_HPP