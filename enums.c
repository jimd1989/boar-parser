#include <string.h>

#include "enums.h"

#define STREQ(s1, s2) (strcmp(s1, s2) == 0)

int
toI(char *s) {
  return
    s == NULL                ? ENUM_OFF              :
    STREQ(s, "off")          ? ENUM_OFF              :
    STREQ(s, "no")           ? ENUM_OFF              :
    STREQ(s, "on")           ? ENUM_ON               :
    STREQ(s, "yes")          ? ENUM_ON               :
    STREQ(s, "fixed")        ? ENUM_ON               :
    STREQ(s, "flat")         ? ENUM_FLAT             :
    STREQ(s, "silence")      ? ENUM_FLAT             :
    STREQ(s, "sine")         ? ENUM_SINE             :
    STREQ(s, "sin")          ? ENUM_SINE             :
    STREQ(s, "rsine")        ? ENUM_SINE        * -1 :
    STREQ(s, "rsin")         ? ENUM_SINE        * -1 :
    STREQ(s, "square")       ? ENUM_SQUARE           :
    STREQ(s, "sq")           ? ENUM_SQUARE           :
    STREQ(s, "rsquare")      ? ENUM_SQUARE      * -1 :
    STREQ(s, "rsq")          ? ENUM_SQUARE      * -1 :
    STREQ(s, "triangle")     ? ENUM_TRIANGLE         :
    STREQ(s, "tri")          ? ENUM_TRIANGLE         :
    STREQ(s, "rtriangle")    ? ENUM_TRIANGLE    * -1 :
    STREQ(s, "rtri")         ? ENUM_TRIANGLE    * -1 :
    STREQ(s, "ramp")         ? ENUM_RAMP             :
    STREQ(s, "saw")          ? ENUM_RAMP             :
    STREQ(s, "rramp")        ? ENUM_RAMP        * -1 :
    STREQ(s, "rsaw")         ? ENUM_RAMP        * -1 :
    STREQ(s, "exponential")  ? ENUM_EXPONENTIAL      :
    STREQ(s, "exp")          ? ENUM_EXPONENTIAL      :
    STREQ(s, "rexponential") ? ENUM_EXPONENTIAL * -1 :
    STREQ(s, "rexp")         ? ENUM_EXPONENTIAL * -1 :
    STREQ(s, "logarithmic")  ? ENUM_EXPONENTIAL      :
    STREQ(s, "log")          ? ENUM_EXPONENTIAL      :
    STREQ(s, "rlogarithmic") ? ENUM_LOGARITHMIC * -1 :
    STREQ(s, "rlog")         ? ENUM_LOGARITHMIC * -1 :
    STREQ(s, "random")       ? ENUM_LOGARITHMIC      :
    STREQ(s, "rand")         ? ENUM_LOGARITHMIC      :
    STREQ(s, "noise")        ? ENUM_SINE             : ENUM_UNKNOWN;
}
