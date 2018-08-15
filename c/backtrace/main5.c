#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_TRACE_ON

typedef struct stack_trace_frame_s {
  const char *file_name;
  int file_line;
  const char *proc_name;
  void *proc_addr;
  struct stack_trace_frame_s *down, *up;
} stack_trace_frame_t;

#define SKIP
typedef enum { TRUE = 1, FALSE = 0 } bool_t;

typedef struct {
  bool_t on;
  struct {
    const char *_begin, *_print, *_return, *_exit, *_end;
  } fmt;
  struct {
    int depth;
    stack_trace_frame_t *lwb, *upb;
  } stack;
  struct {
    int lwb, by, upb;
    const char *prefix;
  } indent;
} stack_trace_t;

extern stack_trace_t stack_trace;

void stack_trace_begin(char *SKIP, stack_trace_frame_t *SKIP);
void stack_trace_end(char *SKIP, int SKIP);
void print_stack_trace();

#ifdef STACK_TRACE_ON

/* Many ThanX to Steve R Bourne for inspiring the following macros ;-) */
#define BEGIN(x)                                                              \
  {                                                                           \
    auto stack_trace_frame_t this = {__FILE__, __LINE__, #x, &x, NULL, NULL}; \
    stack_trace_begin(stack_trace.fmt._begin, &this);                         \
    {
#define RETURN(x)                                       \
  {                                                     \
    stack_trace_end(stack_trace.fmt._return, __LINE__); \
    return (x);                                         \
  }
#define EXIT(x)                                       \
  {                                                   \
    stack_trace_end(stack_trace.fmt._exit, __LINE__); \
    exit(x);                                          \
  }
#define END                                        \
  }                                                \
  stack_trace_end(stack_trace.fmt._end, __LINE__); \
  }

#else

/* Apologies to Landon Curt Noll and Larry Bassel for the following macros :-)
 */
#define BEGIN(x) {
#define RETURN(x) return (x)
#define EXIT(x) exit(x)
#define END }

#define indent_fmt "%s"
#define std_cc_diag_fmt "%s:%d: "
#define stack_trace_diag_fmt " %s[0x%x], stack(depth:%d, size:%u)\n"
#define stack_trace_fmt "%s:%d:\t%s[0x%x]\t--- stack(depth:%d, size:%u) ---\n"

#endif

stack_trace_t stack_trace = {
    FALSE, /* default: stack_trace.on == FALSE */
    {std_cc_diag_fmt "" indent_fmt "BEGIN" stack_trace_diag_fmt,
     stack_trace_fmt,
     std_cc_diag_fmt "" indent_fmt "RETURN" stack_trace_diag_fmt,
     std_cc_diag_fmt "" indent_fmt "EXIT" stack_trace_diag_fmt,
     std_cc_diag_fmt "" indent_fmt "END" stack_trace_diag_fmt},
    {0, (stack_trace_frame_t *)NULL, (stack_trace_frame_t *)NULL}, /* stack */
    {19, 2, 20, "                   "} /* indent wrap */
};

void stack_trace_begin(const char *fmt, stack_trace_frame_t *this) {
  if (stack_trace.on) {
    fprintf(stderr, fmt, this->file_name, this->file_line, /* file details */
            stack_trace.indent.prefix + stack_trace.indent.lwb, this->proc_name,
            this->proc_addr, /* procedure details */
            stack_trace.stack.depth,
            (unsigned)stack_trace.stack.lwb - (unsigned)this);
    stack_trace.indent.lwb = (stack_trace.indent.lwb - stack_trace.indent.by) %
                             stack_trace.indent.upb;
  }

  if (!stack_trace.stack.upb) { /* this IS the stack !! */
    stack_trace.stack.lwb = stack_trace.stack.upb = this;
  } else {
    this->down = stack_trace.stack.upb;
    stack_trace.stack.upb->up = this;
    stack_trace.stack.upb = this;
  }
  stack_trace.stack.depth++;
}

void stack_trace_end(const char *fmt, int line) {
  stack_trace.stack.depth--;
  if (stack_trace.on) {
    stack_trace.indent.lwb = (stack_trace.indent.lwb + stack_trace.indent.by) %
                             stack_trace.indent.upb;
    stack_trace_frame_t *this = stack_trace.stack.upb;
    fprintf(stderr, fmt, this->file_name, this->file_line, /* file details */
            stack_trace.indent.prefix + stack_trace.indent.lwb, this->proc_name,
            this->proc_addr, /* procedure details */
            stack_trace.stack.depth,
            (unsigned)stack_trace.stack.lwb - (unsigned)this);
  }
  stack_trace.stack.upb = stack_trace.stack.upb->down;
}

void print_indent() {
  if (!stack_trace.stack.upb) {
    /* fprintf(stderr, "STACK_TRACE_ON not #defined during compilation\n"); */
  } else {
    stack_trace_frame_t *this = stack_trace.stack.upb;
    fprintf(stderr, std_cc_diag_fmt "" indent_fmt, this->file_name,
            this->file_line, /* file details */
            stack_trace.indent.prefix + stack_trace.indent.lwb);
  }
}

void print_stack_trace() {
  if (!stack_trace.stack.upb) {
    /* fprintf(stderr, "STACK_TRACE_ON not #defined during compilation\n"); */
  } else {
    int depth = stack_trace.stack.depth;
    stack_trace_frame_t *this = stack_trace.stack.upb;
    for (this = stack_trace.stack.upb; this; this = this->down, depth--) {
      fprintf(stderr, stack_trace.fmt._print, this->file_name,
              this->file_line,                  /* file details */
              this->proc_name, this->proc_addr, /* procedure details */
              depth, (unsigned)stack_trace.stack.lwb - (unsigned)this);
    }
    print_indent();
    fprintf(stderr, "--- (depth %d) ---\n", stack_trace.stack.depth);
  }
}

void inner(int k) BEGIN(inner) print_indent();
printf("*** Now dump the stack ***\n");
print_stack_trace();
END

    void
    middle(int x, int y) BEGIN(middle) inner(x *y);
END

    void
    outer(int a, int b, int c) BEGIN(outer) middle(a + b, b + c);
END

    int
    main() BEGIN(main) stack_trace.on = TRUE; /* turn on runtime tracing */
outer(2, 3, 5);
stack_trace.on = FALSE;
RETURN(EXIT_SUCCESS);
END
