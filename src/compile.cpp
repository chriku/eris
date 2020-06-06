#define luai_nummod(L,a,b)      (-1)
#define luai_numpow(L,a,b)      (-1)

#define LUA_IEEE754TRICK

#include "luaconf.h"

#undef LUA_API
#undef LUAI_FUNC
#undef LUAI_DDEC

#define LUA_API consteval
#define LUAI_FUNC consteval
#define LUAI_DDEC constexpr
#define LUA_USE_CTYPE 1
#define getlocaledecpoint() '.'

#include "lua.h"

#define luai_numadd(L,a,b)      ((a)+(b))
#define luai_numsub(L,a,b)      ((a)-(b))
#define luai_nummul(L,a,b)      ((a)*(b))
#define luai_numdiv(L,a,b)      ((a)/(b))
#define luai_numunm(L,a)        (-(a))
#define luai_numeq(a,b)         ((a)==(b))
#define luai_numlt(L,a,b)       ((a)<(b))
#define luai_numle(L,a,b)       ((a)<=(b))
#undef luai_numisnan
#define luai_numisnan(L,a)      (!luai_numeq((a), (a)))

consteval lua_Number strx2number (const char *s, char **endptr) {
  return 0;
}

#define lua_strx2number strx2number

//#include"eris.cpp"
#include"lapi.cpp"
#include"lauxlib.cpp"
#include"lcode.cpp"
#include"lcorolib.cpp"
#include"lctype.cpp"
//#include"ldebug.cpp"
#include"ldo.cpp"
#include"ldump.cpp"
#include"lfunc.cpp"
#include"lgc.cpp"
#include"linit.cpp"
#include"llex.cpp"
#include"lmem.cpp"
#include"lobject.cpp"
#include"lopcodes.cpp"
#include"lparser.cpp"
#include"lstate.cpp"
#include"lstring.cpp"
#include"ltable.cpp"
#include"ltm.cpp"
#include"lundump.cpp"
#include"lvm.cpp"
#include"lzio.cpp"

struct mem_data {
  char* pos;
  char mem[1024*1024];
  LG gstate;
};

consteval void* my_alloc(void* ud, void* ptr, size_t osize, size_t nsize) {
  mem_data* mem=static_cast<mem_data*>(ud);
  if(osize==LUA_TTHREAD) {
    return &(mem->gstate);
  } else {
    auto ret=mem->pos;
    mem->pos+=nsize;
    return ret;
  }
}

consteval void test() {
  mem_data mem;
  mem.pos=mem.mem;
  lua_State*L=lua_newstate(my_alloc, &mem);
}

int main() {
  test();
}
