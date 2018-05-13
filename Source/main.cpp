#include "mbed.h"
#include "duktape/duktape.h"
#include "JSSource.h"

Serial pc(USBTX, USBRX);

static duk_ret_t native_print(duk_context *ctx) {
  pc.printf("%s\n", duk_to_string(ctx, 0));
  return 0;  /* no return value (= undefined) */
}

int main() {
  duk_context *ctx = duk_create_heap_default();
  duk_push_c_function(ctx, native_print, 1);
  duk_put_global_string(ctx, "printf");
  duk_eval_string(ctx, jsSource);
  duk_destroy_heap(ctx);
  return 0;
}
